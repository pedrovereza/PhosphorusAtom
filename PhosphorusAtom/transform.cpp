#include "transform.h"

using namespace std;

Transform::Transform()
{
}

void Transform::SetData(double* data)
{
    int i;

    for (i=0; i<16; i++)
    {
        matrix[i] = (*data);
        data++;
    }
}

Transform::Transform(const Transform &trans)
{
    this->Transform::operator=(trans);
}

void Transform::MakeIdentity()
{
    for (int i=0; i<16; ++i)
        matrix[i] = 0.0;
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0;
}

void Transform::MakeTranslation(const Point4D& translationVector)
{
    MakeIdentity();
    matrix[12] = translationVector.GetX();
    matrix[13] = translationVector.GetY();
    matrix[14] = translationVector.GetZ();
}

void Transform::MakeXRotation(double radians)
{
    MakeIdentity();
    matrix[5] =   cos(radians);
    matrix[9] =  -sin(radians);
    matrix[6] =   sin(radians);
    matrix[10] =  cos(radians);
}

void Transform::MakeYRotation(double radians)
{
    MakeIdentity();
    matrix[0] =   cos(radians);
    matrix[8] =   sin(radians);
    matrix[2] =  -sin(radians);
    matrix[10] =  cos(radians);
}

void Transform::MakeZRotation(double radians)
{
    MakeIdentity();
    matrix[0] =  cos(radians);
    matrix[4] = -sin(radians);
    matrix[1] =  sin(radians);
    matrix[5] =  cos(radians);
}

void Transform::MakeScale(double sX, double sY, double sZ)
{
    MakeIdentity();
    matrix[0] =  sX;
    matrix[5] =  sY;
    matrix[10] = sZ;
}

void Transform::MakeShear(double shX, double shY)
{
    MakeIdentity();
    matrix[8] = shX;
    matrix[9] = shY;
}

Point4D Transform::operator *(const Point4D& point) const
{
    Point4D result;

    return Point4D(  matrix[0]*point.GetX()  + matrix[4]*point.GetY()
                     + matrix[8]*point.GetZ()  + matrix[12]*point.GetW(),
                       matrix[1]*point.GetX()  + matrix[5]*point.GetY()
                     + matrix[9]*point.GetZ()  + matrix[13]*point.GetW(),
                       matrix[2]*point.GetX()  + matrix[6]*point.GetY()
                     + matrix[10]*point.GetZ() + matrix[14]*point.GetW(),
                       matrix[3]*point.GetX()  + matrix[7]*point.GetY()
                     + matrix[11]*point.GetZ() + matrix[15]*point.GetW());
}

Transform Transform::operator*(const Transform &t) const
{
    Transform resultado;
    for (int i=0; i < 16; ++i)
        resultado.matrix[i] =
              matrix[i%4]    *t.matrix[i/4*4]  +matrix[(i%4)+4] *t.matrix[i/4*4+1]
            + matrix[(i%4)+8]*t.matrix[i/4*4+2]+matrix[(i%4)+12]*t.matrix[i/4*4+3];
    return resultado;
}

Transform& Transform::operator=(const Transform& t)
{
    for (int i=0; i < 16; ++i)
        matrix[i] = t.matrix[i];
    return *this;
}

void Transform::CopyMatrix(const Transform& t)
{
    for (int i=0; i < 16; ++i)
        matrix[i] = t.matrix[i];
}

void Transform::Apply(const Transform& t)
{
    CopyMatrix(t * (*this));
}

void Transform::ApplyTo(Point4D* ptPoint) const
{
    ptPoint->SetXYZW(
        matrix[0]*ptPoint->GetX()
            + matrix[4]*ptPoint->GetY()
            + matrix[8]*ptPoint->GetZ()
            + matrix[12]*ptPoint->GetW(),
        matrix[1]*ptPoint->GetX()
            + matrix[5]*ptPoint->GetY()
            + matrix[9]*ptPoint->GetZ()
            + matrix[13]*ptPoint->GetW(),
        matrix[2]*ptPoint->GetX()
            + matrix[6]*ptPoint->GetY()
            + matrix[10]*ptPoint->GetZ()
            + matrix[14]*ptPoint->GetW(),
        matrix[3]*ptPoint->GetX()
            + matrix[7]*ptPoint->GetY()
            + matrix[11]*ptPoint->GetZ()
            + matrix[15]*ptPoint->GetW()
        );
}

void Transform::MakeRotation(const Point4D& refVec, const float radians)
{
    Point4D projEmY;
    Point4D vetTemp;
    Transform tTemp;
    double anguloY;
    double anguloZ;

    //Decompor refVec
    //Angulo em Y (para levar o vetor ao plano XY)
    if (Zero(refVec.GetZ()))
    {
        anguloY = 0.0;
        this->MakeIdentity();
        vetTemp = refVec;
    }
    else
    {
        // se o vetor nao esta no plano XY...
        projEmY.SetXYZW(refVec.GetX(), 0, refVec.GetZ(), 0);
        projEmY.Normalize();
        if (refVec.GetZ() < 0)
            anguloY = -(projEmY.AngleTo(Point4D(1,0,0,0)));
        else
            anguloY = projEmY.AngleTo(Point4D(1,0,0,0));
        this->MakeYRotation(anguloY);
        vetTemp = (*this) * refVec; //refVec no plano XY
    }
    //Angulo em Z (para levar o vetor ao X)
    if (vetTemp.GetY() < 0)
        anguloZ = vetTemp.AngleTo(Point4D(1,0,0,0));
    else
        anguloZ = -(vetTemp.AngleTo(Point4D(1,0,0,0)));
    tTemp.MakeZRotation(anguloZ);
    this->CopyMatrix(tTemp * (*this));
    //Rodar
    tTemp.MakeXRotation(radians);
    this->CopyMatrix(tTemp * (*this));
    //voltar
    tTemp.MakeZRotation(-anguloZ);
    this->CopyMatrix(tTemp * (*this));
    tTemp.MakeYRotation(-anguloY);
    this->CopyMatrix(tTemp * (*this));
}

void Transform::MakeRotation(const Point4D& refPoint, const Point4D& refVec,
                               const float radians)
{
    Transform tTemp;

    this->MakeTranslation(-refPoint);
    tTemp.MakeRotation(refVec, radians);
    this->CopyMatrix(tTemp * (*this));
    tTemp.MakeTranslation(refPoint);
    this->CopyMatrix(tTemp * (*this));
}

void Transform::GetVectorX(Point4D* result) const
{
    result->SetX(matrix[0]);
    result->SetY(matrix[1]);
    result->SetZ(matrix[2]);
    result->SetW(matrix[3]);
}

void Transform::GetVectorY(Point4D* result) const
{
    result->SetX(matrix[4]);
    result->SetY(matrix[5]);
    result->SetZ(matrix[6]);
    result->SetW(matrix[7]);
}

void Transform::GetVectorZ(Point4D* result) const
{
    result->SetX(matrix[8]);
    result->SetY(matrix[9]);
    result->SetZ(matrix[10]);
    result->SetW(matrix[11]);
}

void Transform::GetTranslation(Point4D* result) const
{
    result->SetX(matrix[12]);
    result->SetY(matrix[13]);
    result->SetZ(matrix[14]);
    result->SetW(matrix[15]);
}

#ifndef NDEBUG
bool Transform::HasNaN() const
{
#ifdef __linux__
    for (int i=0; i < 16; ++i)
    {
        if (isnan(matrix[i]))
            return true;
    }
#endif
    return false;
}
#endif

ostream& operator<<(ostream& output, const Transform& t)
{
    int i, j;

    output.setf(ios::showpoint|ios::fixed);
    output.precision(16);
    for (i=0; i<4; ++i)
    {
        for (j=0; j<4; ++j)
            output << setw(12) << t.matrix[i+j*4] << " ";
        output << endl;
    }
    output.unsetf(ios::showpoint|ios::fixed);
    return output;
}

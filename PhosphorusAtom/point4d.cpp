/// \file point4d.cpp
/// \brief Implementation file for V-ART class "Point4d".
/// \version $Revision: 1.6 $

#include "point4d.h"
#include <cmath>

using namespace std;

// Default "less then" comparison uses "LexicographicalLess".
Point4D::tCompareOper Point4D::operatorLess = &Point4D::LexicographicalLess;
float Point4D::xWeight = 1;
float Point4D::yWeight = 1;
float Point4D::zWeight = 1;

Point4D::Point4D()
{
    vetCoord[0]=vetCoord[1]=vetCoord[2]=0;
    vetCoord[3]=1;
}

Point4D::Point4D(const Point4D &point)
{
    vetCoord[0] = point.vetCoord[0];
    vetCoord[1] = point.vetCoord[1];
    vetCoord[2] = point.vetCoord[2];
    vetCoord[3] = point.vetCoord[3];
}

Point4D::Point4D(double x, double y, double z, double w)
// w = 1 (point) by default (see constructor signature)
{
    SetXYZW(x, y, z, w);
}

const Point4D& Point4D::X()
{
    static const Point4D x(1.0,0.0,0.0,0.0);
    return x;
}

const Point4D& Point4D::Y()
{
    static const Point4D y(0.0,1.0,0.0,0.0);
    return y;
}

const Point4D& Point4D::Z()
{
    static const Point4D z(0.0,0.0,1.0,0.0);
    return z;
}

const Point4D& Point4D::DOWN()
{
    static const Point4D down(0.0,-1.0,0.0,0.0);
    return down;
}

const Point4D& Point4D::ORIGIN()
{
    static const Point4D origin(0.0,0.0,0.0,1.0);
    return origin;
}

void Point4D::SetXY(double x, double y)
{
    vetCoord[0] = x;
    vetCoord[1] = y;
}

void Point4D::SetXYZ(double x, double y, double z)
{
    vetCoord[0] = x;
    vetCoord[1] = y;
    vetCoord[2] = z;
}

void Point4D::SetXYZW(double x, double y, double z, double w)
{
    vetCoord[0] = x;
    vetCoord[1] = y;
    vetCoord[2] = z;
    vetCoord[3] = w;
}

void Point4D::Normalize()
// requires that x,y,z and w are not all zeros
{
    if (vetCoord[3] == 0)
    {
        // vector normalization
        double norma = Length();

        vetCoord[0] /= norma;
        vetCoord[1] /= norma;
        vetCoord[2] /= norma;
        vetCoord[3] = 0; // this seems to avoid some round off erros
    }
    else
    {
        // point normalization
        vetCoord[0] /= vetCoord[3];
        vetCoord[1] /= vetCoord[3];
        vetCoord[2] /= vetCoord[3];
        vetCoord[3] = 1;
    }
}

double Point4D::Length() const
{
    return sqrt(vetCoord[0]*vetCoord[0] + vetCoord[1]*vetCoord[1] + vetCoord[2]*vetCoord[2]);
}

double Point4D::DotProduct(const Point4D& p) const
{
    return vetCoord[0]*p.vetCoord[0]+vetCoord[1]*p.vetCoord[1]+vetCoord[2]*p.vetCoord[2];
}

Point4D Point4D::CrossProduct(const Point4D& p) const
{
    return Point4D(GetY()*p.GetZ()-GetZ()*p.GetY(), GetZ()*p.GetX()-GetX()*p.GetZ(), GetX()*p.GetY()-GetY()*p.GetX(), 0);
}

double Point4D::AngleTo(const Point4D& p) const
// Note: This method requires both vectors to be normalized!
{
    double dp = DotProduct(p);
    // Sometimes, the Dot Product is greater then 1 due to floating point errors.
    if (dp > 1.0)
        return 0;
    else
    {
        if (dp < -1.0)
            return 3.1415926535897932384626433832795;
        return acos(dp);
    }
}

double Point4D::GenericAngleTo(const Point4D& p) const
{
    // Sometimes, due to floating point errors, cossine is out of [-1..1], need to check...
    double cosValue = DotProduct(p) / (Length()*p.Length());
    if (cosValue > 1)
        return 0;
    else
    {
        if (cosValue < -1)
            return 3.1415926535897932384626433832795;
        return acos(cosValue);
    }
}

Point4D Point4D::operator-() const
{
    // To keep the nature of the point it seems to me that the w coordinate should
    // not be touched.
    return Point4D(-vetCoord[0], -vetCoord[1], -vetCoord[2], vetCoord[3]);
}

Point4D Point4D::operator-(const Point4D& point) const
{
    return Point4D(vetCoord[0]-point.vetCoord[0],
                     vetCoord[1]-point.vetCoord[1],
                     vetCoord[2]-point.vetCoord[2],
                     vetCoord[3]-point.vetCoord[3]);
}

Point4D Point4D::operator+(const Point4D& vector) const
// This operator should not be used to sum two points. No checking is done, however,
// because clipping algorithms benefit from operating with vetors made from the
// subtraction of non-normalized points. There is no easy way to know the nature
// data being processed here.
{
    return Point4D(vetCoord[0]+vector.vetCoord[0],
                         vetCoord[1]+vector.vetCoord[1],
                         vetCoord[2]+vector.vetCoord[2],
                         vetCoord[3]+vector.vetCoord[3]);
}

void Point4D::operator+=(const Point4D& vector)
// Requires that the active object (a point) be normalized.
{
    vetCoord[0] += vector.vetCoord[0];
    vetCoord[1] += vector.vetCoord[1];
    vetCoord[2] += vector.vetCoord[2];
}

Point4D Point4D::operator*(double escalar) const
{
    return Point4D(vetCoord[0]*escalar,
                         vetCoord[1]*escalar,
                         vetCoord[2]*escalar,
                         vetCoord[3]*escalar);
}

void Point4D::operator*=(double escalar)
{
    vetCoord[0]*=escalar;
    vetCoord[1]*=escalar;
    vetCoord[2]*=escalar;
    vetCoord[3]*=escalar;
}

bool Point4D::operator==(const Point4D& point) const
{
    return (vetCoord[0] == point.vetCoord[0]) &&
           (vetCoord[1] == point.vetCoord[1]) &&
           (vetCoord[2] == point.vetCoord[2]) &&
           (vetCoord[3] == point.vetCoord[3]);
}

bool Point4D::operator<(const Point4D& p) const
{
    return (this->*operatorLess)(p);
}

bool Point4D::operator!=(const Point4D& point) const
{
    return (vetCoord[0] != point.vetCoord[0]) ||
           (vetCoord[1] != point.vetCoord[1]) ||
           (vetCoord[2] != point.vetCoord[2]) ||
           (vetCoord[3] != point.vetCoord[3]);
}

void Point4D::operator=(const Point4D& point)
{
    vetCoord[0] = point.vetCoord[0];
    vetCoord[1] = point.vetCoord[1];
    vetCoord[2] = point.vetCoord[2];
    vetCoord[3] = point.vetCoord[3];
}

Point4D Point4D::operator/( double escalar ) const
{
    return Point4D(vetCoord[0]/escalar,
                         vetCoord[1]/escalar,
                         vetCoord[2]/escalar,
                         vetCoord[3]/escalar);
}

bool Point4D::LexicographicalLess(const Point4D& p) const
{
    if (vetCoord[0] == p.vetCoord[0])
    {
        if (vetCoord[1] == p.vetCoord[1])
        {
            if (vetCoord[2] == p.vetCoord[2])
                return vetCoord[3] < p.vetCoord[3];
            else
                return vetCoord[2] < p.vetCoord[2];
        }
        else
            return vetCoord[1] < p.vetCoord[1];
    }
    else
        return vetCoord[0] < p.vetCoord[0];
}

bool Point4D::XThenZLess(const Point4D& p) const
{
    if (vetCoord[0] == p.vetCoord[0])
        return vetCoord[2] < p.vetCoord[2];
    else
        return vetCoord[0] < p.vetCoord[0];
}

bool Point4D::YThenXLess(const Point4D& p) const
{
    if (vetCoord[1] == p.vetCoord[1])
        return vetCoord[0] < p.vetCoord[0];
    else
        return vetCoord[1] < p.vetCoord[1];
}

bool Point4D::YThenZLess(const Point4D& p) const
{
    if (vetCoord[1] == p.vetCoord[1])
        return vetCoord[2] < p.vetCoord[2];
    else
        return vetCoord[1] < p.vetCoord[1];
}

bool Point4D::ZThenXLess(const Point4D& p) const
{
    if (vetCoord[2] == p.vetCoord[2])
        return vetCoord[0] < p.vetCoord[0];
    else
        return vetCoord[2] < p.vetCoord[2];
}

bool Point4D::ZThenYLess(const Point4D& p) const
{
    if (vetCoord[2] == p.vetCoord[2])
        return vetCoord[1] < p.vetCoord[1];
    else
        return vetCoord[2] < p.vetCoord[2];
}

bool Point4D::WeightedLess(const Point4D& p) const
{
    return WeightedSum() < p.WeightedSum();
}

bool Point4D::WeightedGreater(const Point4D& p) const
{
    return WeightedSum() > p.WeightedSum();
}

float Point4D::WeightedSum() const
{
    return (vetCoord[0] * xWeight) + (vetCoord[1] * yWeight) + (vetCoord[2] * zWeight);
}

namespace VART
{
    ostream& operator<<(ostream& output, const Point4D& p)
    {
        output.setf(ios::fixed);
        output.precision(5);
        output << "(" << p.GetX() << "," << p.GetY() << "," << p.GetZ() << ","
               << p.GetW() << ")";
        output.unsetf(ios::fixed);
        return output;
    }
}

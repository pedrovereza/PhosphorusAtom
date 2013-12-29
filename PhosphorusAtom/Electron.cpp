#include "Electron.h"

void Electron::move(Transform translationMatrix)
{
	matrix = translationMatrix;

	rotationAngle = (int)(rotationAngle + 5) % 360;
}

double Electron::getRotationAngle()
{
	return rotationAngle;
}

double Electron::getOrbitAngle()
{
	return orbitAngle;
}

void Electron::draw()
{
	glPushMatrix();

	GLfloat BLUE[] = {0, 0, 1};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BLUE);

	glColor3ub(0,0,255);
	glMultMatrixd(matrix.GetData());
	glutSolidSphere(0.75, 12, 24);
	glPopMatrix();
}
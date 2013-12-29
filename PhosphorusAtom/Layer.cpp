#include "Layer.h"

void Layer::addElectron()
{
	double orbitAngle = ((M_PI * (electrons.size() + 2))/electronsInAtom) * (180/M_PI);

	Electron electron = Electron(orbitAngle);

	electrons.push_back(electron);
}

void Layer::draw()
{
	Electron* electron;

	for (auto it = electrons.begin(); it != electrons.end(); it++)
	{
		electron = &(*it);
		drawOrbit(electron->getOrbitAngle());

		electron->draw();
	}
}

void Layer::moveElectrons()
{
	Electron* electron;
	Transform translationMatrix;
	Transform identityMatrix;

	identityMatrix.MakeIdentity(); //usado para nao alterar a matriz do eletron

	for (auto it = electrons.begin(); it != electrons.end(); it++)
	{
		electron = &(*it);

		translationMatrix = transformer.makeTranslation(identityMatrix, getPositionInOrbit(electron->getRotationAngle(), radius, electron->getOrbitAngle()));

		electron->move(translationMatrix);
	}
}

double Layer::toRadians(double angle)
{
	return (M_PI/180) * angle;
}

Point4D Layer::getPositionInOrbit(double rotationAngle, double raio, double orbitAngle) {
	double x = (raio * cos(toRadians(rotationAngle)) * cos(toRadians(orbitAngle)));
	double y = (raio * sin(toRadians(rotationAngle)) * cos(toRadians(orbitAngle)));
	double z = (raio * sin(toRadians(rotationAngle)));

	return Point4D(x,y,z);
}

void Layer::drawOrbit(double orbitAngle)
{
	GLfloat WHITE [] = {1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, WHITE);
	for(int i = 0; i < 360; i+= 5)
	{
		glBegin(GL_POINTS);
		
		Point4D positioninOrbit = getPositionInOrbit(i, radius, orbitAngle);
		glVertex3d(positioninOrbit.GetX(), positioninOrbit.GetY(), positioninOrbit.GetZ());
		glEnd();
	}
}
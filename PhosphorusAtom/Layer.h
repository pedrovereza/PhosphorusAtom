#define _USE_MATH_DEFINES

#include <math.h>
#include <vector>
#include "Electron.h"
#include "Transformer.h"

#pragma once;

using namespace std;

class Layer
{
private:
	vector<Electron> electrons;
	double radius;
	int electronsCount;
	int electronsInAtom;
	Transformer transformer;

	void drawOrbit(double orbitAngle);

	Point4D getPositionInOrbit(double rotationAngle, double raio, double orbitAngle);

	double toRadians(double angle);

public:

	Layer()
	{
	}

	Layer(int electronsInAtom, int electronsCount, double radius)
	{
		this->electronsInAtom = electronsInAtom;
		this-> radius = radius;

		for (int i = 0; i < electronsCount; i++)
			addElectron();
	}

	void addElectron();
	void draw();
	void moveElectrons();
};
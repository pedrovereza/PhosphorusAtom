#include "transform.h"

#include "OpenGL.h"

#pragma once

class Electron
{
private:
	Transform matrix;
	double orbitAngle;
	double rotationAngle;

public:
	Electron(double orbitAngle)
	{
		matrix.MakeIdentity();
		this->orbitAngle = orbitAngle;

		rotationAngle = rand() % 360;
	}

	void draw();

	double getOrbitAngle();
	double getRotationAngle();

	void move(Transform translationMatrix);
};
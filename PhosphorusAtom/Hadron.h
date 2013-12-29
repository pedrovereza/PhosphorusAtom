#include "OpenGL.h"
#include "transform.h"

#pragma once;

class Hadron
{
private:
	GLfloat color[3];

	Transform matrix;

	Hadron()
	{
		matrix.MakeIdentity();
	}

	Hadron(GLfloat* color)
	{
		matrix.MakeIdentity();

		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
	}

public:

	static Hadron createNeutron()
	{ 
		GLfloat GREEN[] = {0.0, 1.0, 0.0};	
		return Hadron(GREEN);
	}

	static Hadron createProton()
	{ 
		GLfloat PURPPLE[] = {1.0, 0.0, 1.0};
		return Hadron(PURPPLE);
	}


	Transform getMatrix()
	{
		return matrix;
	}

	void setMatrix(Transform matrix)
	{
		this->matrix = matrix;
	}

	void draw()
	{
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

		glMultMatrixd(getMatrix().GetData());
		glutSolidSphere(1, 12, 24);

		glPopMatrix();
	}
};
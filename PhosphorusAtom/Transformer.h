#include "transform.h"

#pragma once

class Transformer
{
private:
	static const double ONE_DEGREE_IN_RADIANS;

	Transform translationMatrix;
public:

	Transformer()
	{
	}

	Transform makeTranslation(Transform matrix, Point4D point);
};
#include "Transformer.h"

const double Transformer::ONE_DEGREE_IN_RADIANS = 0.017453292519943295769236907684886;

Transform Transformer::makeTranslation(Transform matrix, Point4D point)
{
	translationMatrix.MakeTranslation(point);

	return matrix * translationMatrix;
}
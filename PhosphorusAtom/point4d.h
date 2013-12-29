#include <iostream>

#pragma once

class Point4D {
	/// Output operator
	// FixMe: Perhaps this will cause trouble on an application with no console...
	friend std::ostream& operator<<(std::ostream& output, const Point4D& p);

	/// Type for comparison operators
	typedef bool (Point4D::*tCompareOper)(const Point4D&) const;
public:
	// PUBLIC METHODS
	/// Creates the (0,0,0,1) point.
	Point4D();
	Point4D(const Point4D& point);
	Point4D(double x, double y, double z = 0, double w = 1.0);

	Point4D operator-() const;
	bool operator==(const Point4D& point) const;
	bool operator!=(const Point4D& point) const;
	void operator=(const Point4D& point);

	/// \brief Checks whether a point is "less then" other.
	///
	/// The idea of ordering in 4D point comes from operatorLess public
	/// attribute.
	bool operator<(const Point4D& p) const;

	/// \brief Verifies whether a point is less than other by looking at
	/// coordinates in lexicographical (x, y, z then w) order.
	bool LexicographicalLess(const Point4D& p) const;

	/// \brief Verifies whether a point is less then other by looking at
	/// coordinates X, then Z only.
	bool XThenZLess(const Point4D& p) const;
	bool YThenXLess(const Point4D& p) const;
	bool YThenZLess(const Point4D& p) const;
	bool ZThenXLess(const Point4D& p) const;
	bool ZThenYLess(const Point4D& p) const;
	bool WeightedLess(const Point4D& p) const;
	bool WeightedGreater(const Point4D& p) const;

	/// \brief Addition for point and vector (or vice versa).
	///
	/// Both point and vector should be normalized.
	/// \return a (translated) point.
	Point4D operator+(const Point4D& vector) const;
	void operator+=(const Point4D& vector);

	/// \brief Subtraction of two points.
	///
	/// Both points should be normalized.
	/// \return a vector (from "point" to "this").
	Point4D operator-(const Point4D& point) const;
	Point4D operator*(double escalar) const;
	void operator*=(double escalar);

	Point4D operator/( double escalar ) const;

	double GetX() const { return vetCoord[0]; }
	double GetY() const { return vetCoord[1]; }
	double GetZ() const { return vetCoord[2]; }
	double GetW() const { return vetCoord[3]; }

	/// \brief Returns vertex coordinates as a pointer to 4 doubles.
	///
	/// This method is usefull to pass to glVertex4dv().
	const double* VetXYZW() const { return vetCoord; }

	/// \brief Computes the dot product between "this" and "p".
	double DotProduct(const Point4D& p) const;

	/// \brief Computes the angle up to p.
	///
	/// Requires both vectors to be normalized.
	/// Use Point4D::GenericAngleTo(const Point4D& p) to avoid vectors normalization.
	/// \return the angle in radians of the smaller arc between "this" and "p".
	double AngleTo(const Point4D& p) const;

	/// This method doesn't require both vectors to be normalized, but has poorer
	/// performance than Point4D::AngleTo(const Point4D& p) method.
	/// \return the angle in radians of the smaller arc between "this" and "p".
	double GenericAngleTo(const Point4D& p) const;

	/// \brief Computes the cross product between "this" and "p".
	Point4D CrossProduct(const Point4D& p) const;

	void SetX(double x) { vetCoord[0] = x; }
	void SetY(double y) { vetCoord[1] = y; }
	void SetZ(double z) { vetCoord[2] = z; }
	void SetW(double w) { vetCoord[3] = w; }
	void SetXY(double x, double y);
	void SetXYZ(double x, double y, double z);
	void SetXYZW(double x, double y, double z, double w);

	/// \brief Normalizes the point/vector.
	///
	/// Points are normalized by dividing coordinates by W. Vectors are
	/// normalized by having their length changed to 1. Warning: The homogeneous
	/// point (0,0,0,0) is neither a point nor a vector and will cause a division
	/// by zero!
	void Normalize();
	double Length() const;
	// PUBLIC STATIC METHODS
	/// The (0,-1,0,0) vector.
	static const Point4D& DOWN();
	/// The (0,0,0,1) point.
	static const Point4D& ORIGIN();
	/// The X vector (1,0,0,0).
	static const Point4D& X();
	/// The Y vector (0,1,0,0).
	static const Point4D& Y();
	/// The Z vector (0,0,1,0).
	static const Point4D& Z();
	// PUBLIC STATIC ATTRIBUTES
	/// \brief Points to the operator to use within operator<.
	///
	/// The application programmer should change this pointer to the desired
	/// comparison function. Default value is LexicographicalLess. To change its
	/// value, use something like: Point4D::operatorLess = &Point4D::LexicographicalLess .
	/// Currently, possible values are: LexicographicalLess and XThenZLess.
	static tCompareOper operatorLess;

	/// \brief Weight of the X coordinate for Weighted comparisons.
	static float xWeight;
	/// \brief Weight of the Y coordinate for Weighted comparisons.
	static float yWeight;
	/// \brief Weight of the Z coordinate for Weighted comparisons.
	static float zWeight;
private:
	double vetCoord[4];
	float WeightedSum() const;
}; // end class declaration


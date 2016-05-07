
#include <cmath>

#include "Plane.h"
#include "Point.h"

Plane::Plane() : X(0), Y(0), Z(0), W(0)
{
}

Plane::Plane(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w)
{
}

Plane::Plane(const Point & point, const Point & normal)
{
	X = normal.X;
	Y = normal.Y;
	Z = normal.Z;
	W = normal.X*(-1 * point.X) + normal.Y*(-1 * point.Y) + normal.Z*(-1 * point.Z);
}

void Plane::SetPlain(const Point & point, const Point & normal)
{
	X = normal.X;
	Y = normal.Y;
	Z = normal.Z;
	W = normal.X*(-1 * point.X) + normal.Y*(-1 * point.Y) + normal.Z*(-1 * point.Z);
}

double Plane::GetDistance(const Point & point) const
{
	return (abs(X*point.X + Y*point.Y+ Z*point.Z+W)/(sqrt(X*X+Y*Y+Z*Z)));
}



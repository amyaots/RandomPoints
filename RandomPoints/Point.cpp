#include <cstdlib>
#include <vector>

#include "Plane.h"
#include "Point.h"


double Rand(double min, double max)
{
	return (double)(rand()) / RAND_MAX*(max - min) + min;
}

Point Point::operator-(const Point& p)
{	
	return Point(X - p.X, Y - p.Y, Z - p.Z);
}

Point Point::operator+(const Point& p)
{
	return Point(X + p.X, Y + p.Y, Z + p.Z);
}


bool AreDoubleSame(double dFirstVal, double dSecondVal)
{
	return std::fabs(dFirstVal - dSecondVal) < std::numeric_limits<double>::epsilon();
}


bool Point::operator==(const Point & p) const
{
	return (AreDoubleSame(X, p.X) && AreDoubleSame(Y, p.Y) && AreDoubleSame(Z, p.Z));
}


double Point::GetLength() const
{
	return sqrt(X*X + Y*Y + Z*Z);
}

double Point::DotProduct(const Point & p)
{
	if ((this->GetLength() * p.GetLength()) > 0)
	{
		return (X*p.X + Y*p.Y + Z*p.Z) / (this->GetLength() * p.GetLength());
	}
	else
	{
		return 0.0;
	}
}

double Point::DotProduct(const Point & first, const Point & second)
{
	if ((first.GetLength() * second.GetLength()) > 0)
	{
		return (first.X*second.X + first.Y*second.Y + first.Z*second.Z) / (first.GetLength() * second.GetLength());
	}
	else
	{
		return 0.0;
	}
}

Point Point::CrossProduct(const Point & p) const
{
	return Point(Y*p.Z - Z*p.Y, Z*p.X - X*p.Z, X*p.Y - Y*p.X);
}

Point Point::CrossProduct(const Point & first, const Point & second)
{
	return Point(first.Y*second.Z - first.Z*second.Y, first.Z*second.X - first.X*second.Z, first.X*second.Y - first.Y*second.X);
}

Point Point::FindVec(const Point & p)
{
	return Point(p.X-X, p.Y-Y,p.Z-Z);
}

Point Point::FindVec(const Point & first, const Point & second)
{
	return Point(second.X-first.X, second.Y - first.Y, second.Z - first.Z);
}

Point Point::GetRandomPointInBox(const Point& Min, const Point& Max)
{
	return Point( Rand(Min.X, Max.X)
				, Rand(Min.Y, Max.Y)
				, Rand(Min.Z, Max.Z));
}

Point Point::GetMiddlePoint(const Point & Min, const Point & Max)
{
	return Point( (Min.X + Max.X) / 2.0
				, (Min.Y + Max.Y) / 2.0
				, (Min.Z + Max.Z) / 2.0);
}

Point Point::GetProjectionPoint(const Plane & plain, const Point & point)
{
	double down = plain.X  * plain.X + plain.Y * plain.Y + plain.Z * plain.Z + plain.W;
	double up = point.X  * plain.X + point.Y * plain.Y + point.Z * plain.Z + plain.W;
	double Param = up / down;

	return Point(Param*plain.X+point.X, Param*plain.Y + point.Y, Param*plain.Z + point.Z);
}

Point operator*(const double& la, const Point& rp)
{	
	return Point(la * rp.X, la * rp.Y, la * rp.Z);
}

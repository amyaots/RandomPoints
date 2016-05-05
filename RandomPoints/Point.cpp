#include <cstdlib>
#include <vector>

#include "Plain.h"
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

bool Point::operator<(const Point & p) const
{
	if (X < p.X && Y < p.Y && Z < p.Z)
	{
		return true;
	}
	else if (X < p.X && Y < p.Y && Z == p.Z)
	{
		return true;
	}
	else if (X == p.X && Y < p.Y && Z == p.Z)
	{
		return true;
	}
	else if (X < p.X && Y == p.Y && Z == p.Z)
	{
		return true;
	}
	else if (X == p.X && Y == p.Y && Z < p.Z)
	{
		return true;
	}
	else if (X == p.X && Y < p.Y && Z < p.Z)
	{
		return true;
	}
	else if (X < p.X && Y == p.Y && Z < p.Z)
	{
		return true;
	}
	else
	{
		return false;
	}
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

Point Point::GetProjectionPoint(const Plain & plain, const Point & point)
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

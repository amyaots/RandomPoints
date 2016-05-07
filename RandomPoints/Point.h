#pragma once

#include <ostream>

std::ostream& operator<<(std::ostream& out, const class Point& p);

class Point
{

public:
	Point() : X(0), Y(0), Z(0)
	{
	};
	Point(double x, double y, double z) : X(x), Y(y), Z(z)
	{
	};
	double X;
	double Y;
	double Z;

	Point operator-(const Point& p);
	Point operator+(const Point& p);
	friend Point operator*(const double& la, const Point& rp);
	bool operator<(const Point& p) const;
	bool operator!=(const Point& p) const;

	friend std::ostream& operator<<(std::ostream& out, const Point& p);

	double GetLength() const;
	
	double DotProduct(const Point& p);
	static double DotProduct(const Point& first, const Point& second);

	Point FindVec(const Point& p);
	static Point FindVec(const Point& first, const Point& second);

	static Point GetRandomPointInBox(const Point& Min, const Point& Max);
	static Point GetMiddlePoint(const Point& Min, const Point& Max);
	static Point GetProjectionPoint(const class Plane& plain, const Point& point);
};

inline std::ostream& operator<<(std::ostream& out, const Point& p)
{
	return out << "X: " << p.X << "\t"
		<< "Y: " << p.Y << "\t"
		<< "Z: " << p.Z << "\n";
}
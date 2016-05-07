#pragma once

class Plane
{
public:
	Plane();
	Plane(double x, double y, double z, double w);
	Plane(const class Point& point, const class Point& normal);

	void SetPlain(const class Point& point, const class Point& normal);
	double GetDistance(const class Point& point) const;

	double X, Y, Z, W;
};


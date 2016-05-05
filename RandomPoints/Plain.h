#pragma once

class Plain
{
public:
	Plain();
	Plain(double x, double y, double z, double w);
	Plain(const class Point& point, const class Point& normal);

	void SetPlain(const class Point& point, const class Point& normal);
	double GetDistance(const class Point& point) const;

	double X, Y, Z, W;
};


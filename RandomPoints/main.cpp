#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Point.h"
#include "Plane.h"

Point FindMin(const std::vector<Point>& vec)
{
	std::cout << "Search min point..." << std::endl;
	if (vec.size() > 0)
	{
		Point Min = *std::min_element(vec.begin(), vec.end());

		return Min;
	}
	else
	{
		return Point();
	}
}

Point FindAxis(const Point& normal)
{
	std::vector<Point> Axes;
	Axes.push_back(Point(1.0, 0.0, 0.0));
	Axes.push_back(Point(0.0, 1.0, 0.0));
	Axes.push_back(Point(0.0, 0.0, 1.0));

	Point Axis;
	double max{ 0 };

	for (const Point& axis : Axes)
	{
		if (max < abs(Point::DotProduct(normal, axis)))
		{
			Axis = axis;
		}
	}

	return Axis;
}

void FilterPoints(std::vector<Point>& vec, const Plane& plain, const double D)
{
	for (auto it = vec.begin(); it != vec.end();)
	{
		if (plain.GetDistance(*it) > D)
		{
			it = vec.erase(it);
		}
		else
		{
			*it = Point::GetProjectionPoint(plain, *it);
			++it;
		}
	}
}

Point Search(std::vector<Point>& data, const Point& Vector, const Point& Current, const Point& Prev = Point(0,0,0))
{
	Point Next;
	double MinCos{ 2 };
	
	for (auto it = data.begin(); it!=data.end();)
	{
		Point Vec = Point::FindVec(Current, *it);
		if (Vec.GetLength()>0)
		{
			double currCos = Point::DotProduct(Vector, Vec);
			if (MinCos > currCos && *it != Prev)
			{
				MinCos = currCos;
				Next = *it;
			}
		}

		++it;
	}
	return Next;
}

std::vector<Point> ConvexHullJarvis(std::vector<Point>& vec, const Point& axis)
{
	std::vector<Point> Result;

	Result.push_back(FindMin(vec));
	Result.push_back(Search(vec, axis, Result.front()));
	size_t index{ 1 };
	do
	{
		Point Current = Result.at(index);
		Point Vector = Point::FindVec(Result.at(index - 1), Current);
		Result.push_back(Search(vec, Vector, Current, Result.at(index - 1)));
		++index;
	} while (Result.front() != Result.back());
	Result.pop_back();
	return std::move(Result);
}


int main()
{
	srand((unsigned int)time(0));
	std::cout << "Enter Min point :" << std::endl;
	Point Min(0, 0, 0);
	std::cin >> Min.X;
	std::cin >> Min.Y;
	std::cin >> Min.Z;
	std::cout << "Min point :\t" <<Min<< std::endl;

	std::cout << "Enter Max point :" << std::endl;
	Point Max(0, 0, 0);
	std::cin >> Max.X;
	std::cin >> Max.Y;
	std::cin >> Max.Z;
	std::cout << "Max point :\t" << Max << std::endl;

	Point RandomPoint = Point::GetRandomPointInBox(Min, Max);
	std::cout << "Random point :\t" << RandomPoint << std::endl;
	std::vector<Point> RandomPoints;
	
	std::ofstream out("points.txt");

	for (size_t iP = 0; iP < 100000; iP++)
	{
		RandomPoints.push_back(Point::GetRandomPointInBox(Min, Max));
	}

	std::cout << "Enter normal :" << std::endl;
	Point Normal(0, 0, 0);
	std::cin >> Normal.X;
	std::cin >> Normal.Y;
	std::cin >> Normal.Z;
	std::cout << "Normal :\t" << Normal << std::endl;
	std::cout << "Middle :\t" << Point::GetMiddlePoint(Min, Max) << std::endl;

	Plane CutPlain(Point::GetMiddlePoint(Min, Max), Normal);

	std::cout << "Enter D :" << std::endl;
	double D{ 0 };
	std::cin >> D;

	FilterPoints(RandomPoints, CutPlain, D);
	std::cout << "Finish filtering." << std::endl;
	std::cout << "Start find convex hull..." << std::endl;
	std::vector<Point> ResultPoints = ConvexHullJarvis(RandomPoints, FindAxis(Normal));

	for (const Point& P: ResultPoints)
	{
		std::cout << P << std::endl;
	}

	out.close();
	system("pause");
	return 0;
}
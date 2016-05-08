#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

#include "Point.h"
#include "Plane.h"

void FindMin(std::vector<Point>& vec, const Point& Middle)
{
	double MaxDistance{ 0 };
	std::vector<Point>::iterator Min;
	if (vec.size() > 0)
	{
		for (auto it = vec.begin(); it!=vec.end(); ++it)
		{
			double CurrDistance = Point::FindVec(Middle, *it).GetLength();
			if (MaxDistance < CurrDistance)
			{
				MaxDistance = CurrDistance;
				Min = it;
			}
		}

		Point Insert = *Min;
		vec.erase(Min);
		vec.insert(vec.begin(), Insert);
	}
	return;
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


std::vector<Point> ConvexHull(std::vector<Point>& vec, const Point& normal, const Point& middle)
{	
	FindMin(vec, middle);

	Point Cross = Point::CrossProduct(Point::FindVec(vec.front(), middle), normal);
	std::sort(vec.begin() + 1, vec.end(), [&](const Point& f, const Point& s) 
											{
												return Point::DotProduct(Cross, Point::FindVec(vec.front(), f))
													 > Point::DotProduct(Cross, Point::FindVec(vec.front(), s));
											});

	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

	std::vector<Point> Result;
	Result.push_back(*vec.begin());
	Result.push_back(*(vec.begin()+1));
	Result.push_back(*(vec.begin()+2));

	Point nextPoint;
	Point prevPoint;
	Point currentPoint;
	std::vector<Point>::iterator jt;

	for (auto it = vec.begin() + 3; it != vec.end(); it++)
	{
		currentPoint = *it;
		Result.push_back(currentPoint);

		nextPoint = currentPoint;
		for (jt = Result.begin() + Result.size() - 2; jt-1 != Result.begin(); jt--)
		{
			currentPoint = *jt;
			prevPoint = *(jt - 1);

			if (Point::DotProduct(Point::CrossProduct(Point::FindVec(currentPoint,nextPoint), Point::FindVec(currentPoint, prevPoint)), normal) > 0)
			{
				Result.pop_back();
			}
			else
			{
				break;
			}
		}
	}
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

	std::vector<Point> RandomPoints;
	for (size_t iP = 0; iP < 1000000; iP++)
	{
		RandomPoints.push_back(Point::GetRandomPointInBox(Min, Max));
	}

	std::cout << "Enter normal :" << std::endl;
	Point Normal(0, 0, 0);
	std::cin >> Normal.X;
	std::cin >> Normal.Y;
	std::cin >> Normal.Z;
	std::cout << "Normal :\t" << Normal << std::endl;

	Plane CutPlain(Point::GetMiddlePoint(Min, Max), Normal);

	std::cout << "Enter D :" << std::endl;
	double D{ 0 };
	std::cin >> D;

	FilterPoints(RandomPoints, CutPlain, D);
	std::cout << "Finish filtering." << std::endl;

	std::cout << "Start find convex hull..." << std::endl;
	std::vector<Point> ResultPoints = ConvexHull(RandomPoints, Normal, Point::GetMiddlePoint(Min, Max));

	std::string Path;
	std::cout << "Enter path for text document (results):" << std::endl;
	std::cin >> Path;
	Path += "Result.txt";
	std::ofstream out(Path.c_str());

	for (const Point& P: ResultPoints)
	{
		out.setf(std::ios_base::fixed, std::ios_base::floatfield);
		out.precision(5);
		out << P << std::endl;
	}

	out.close();
	system("pause");
	return 0;
}
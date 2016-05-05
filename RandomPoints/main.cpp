#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Point.h"
#include "Plain.h"

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

	for (int32_t iP = 0; iP < 1000000; iP++)
	{
		RandomPoints.push_back(Point::GetRandomPointInBox(Min, Max));
	}

	std::cout << "Enter normal :" << std::endl;
	Point Normal(0, 0, 0);
	std::cin >> Normal.X;
	std::cin >> Normal.Y;
	std::cin >> Normal.Z;
	std::cout << "Normal :\t" << Normal << std::endl;

	Point X(1.0, 0.0, 0.0);
	Point Y(0.0, 1.0, 0.0);
	Point Z(0.0, 0.0, 1.0);
	double XDot = Point::DotProduct(Normal, X);
	double YDot = Point::DotProduct(Normal,Y);
	double ZDot = Point::DotProduct(Normal,Z);

	std::cout << "Dot products with normals: " << XDot << "\t" << YDot << "\t" << ZDot << "\n";
	
	out.close();
	system("pause");
	return 0;
}
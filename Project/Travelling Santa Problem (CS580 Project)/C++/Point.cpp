#include "Point.h"

Point::Point()
	{
		this->identify = 0;
		this->horizontalCoordinate = 0;
		this->verticalCoordinate = 0;
	}

Point::Point(int id, int hc, int vc)
	{
		this->identify = id;
		this->horizontalCoordinate = hc;
		this->verticalCoordinate = vc;
	}

Point::Point(const Point& src)
	{
		this->identify = src.identify;
		this->horizontalCoordinate = src.horizontalCoordinate;
		this->verticalCoordinate = src.verticalCoordinate;
	}

void Point::display(std::ostream& outFile) const
{
	outFile << "ID: " << this->identify << ' ' << '(' << this->horizontalCoordinate << ',' << this->verticalCoordinate << ")";
}

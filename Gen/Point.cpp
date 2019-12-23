#include "Point.h"

#include <cmath>


Point::Point(const int label, const int x, const int y) :
	label(label), x(x), y(y)
{}


Point::Point(std::istream &in)
{
	in >> label >> x >> y;
}


Point::~Point()
{}


double Point::distance(const Point &other) const
{
	int difx = x - other.x,
		dify = y - other.y;
	return sqrt(difx * difx + dify * dify);
}


std::ostream& operator<<(std::ostream &out, const Point &point)
{
	out << point.label << " " << point.x << " " << point.y;
	return out;
}
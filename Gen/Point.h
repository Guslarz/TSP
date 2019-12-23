#pragma once

#include <iostream>


class Point
{
	int label, x, y;

public:
	Point(int, int, int);
	Point(std::istream&);

	~Point();

	double distance(const Point&) const;

	friend std::ostream& operator<<(std::ostream&, const Point&);
};


std::ostream& operator<<(std::ostream&, const Point&);
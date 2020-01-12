#pragma once

#include "Point.h"

#include <vector>


class Instance
{
	std::vector<Point> points;

public:
	Instance(const std::string&);

	~Instance();

	size_t getN() const { return points.size(); }
	const std::vector<Point>& getPoints() const { return points; }
	const Point& getCity(size_t i) const { return points[i]; }

	static void generate(const std::string&, const size_t, const int);

	friend std::ostream& operator<<(std::ostream&, const Instance&);

private:
	void operator<<(std::istream&);
};


std::ostream& operator<<(std::ostream&, const Instance&);

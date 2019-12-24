#pragma once

#include "Chromosome.h"

#include <chrono>


using duration_t = std::chrono::duration<double>;
using timepoint_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Result
{
	const size_t n;
	const unsigned int generation;
	const Chromosome &chromosome;
	const duration_t duration;

public:
	Result(const size_t, const unsigned int, const Chromosome&, const duration_t);
	~Result();

	friend std::ostream& operator<<(std::ostream&, const Result&);
};


std::ostream& operator<<(std::ostream&, const Result&);

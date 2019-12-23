#pragma once

#include "Crossover.h"


class SequentialConsecutiveCrossover :
	public Crossover
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

public:
	SequentialConsecutiveCrossover(const size_t, const distarr_t&, randgen_t&);
	~SequentialConsecutiveCrossover();

	Chromosome* operator()(const Chromosome&, const Chromosome&);
};


#pragma once

#include "Chromosome.h"


class ChromosomeInitializer
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

	gene_t first;

public:
	ChromosomeInitializer(const size_t, const distarr_t&, randgen_t&);
	~ChromosomeInitializer();

	Chromosome* operator()();

private:
	void randomInitialize(Chromosome&) const;
	void greedyInitialize(Chromosome&) const;
};


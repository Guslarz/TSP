#pragma once

#include "ChromosomeAsEdges.h"


class ChromosomeInitializer
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

	gene_t first;

public:
	ChromosomeInitializer(const size_t, const distarr_t&, randgen_t&);
	~ChromosomeInitializer();

	chromosomeptr_t operator()();

private:
	void randomInitialize(ChromosomeAsEdges&) const;
	void greedyInitialize(ChromosomeAsEdges&) const;
	chromosomeptr_t fromEdges(const ChromosomeAsEdges&) const;
};


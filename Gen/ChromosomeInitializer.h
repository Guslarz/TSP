#pragma once

#include "Chromosome.h"


class ChromosomeInitializer
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

	gene_t index;
	const gene_t improvedLimit;
	std::vector<chromosomeptr_t> greedyChromosomes;

public:
	ChromosomeInitializer(const size_t, const distarr_t&, randgen_t&);
	~ChromosomeInitializer();

	chromosomeptr_t operator()();

private:
	void randomInitialize(Chromosome&) const;
	void greedyInitialize(Chromosome&) const;
	void improve(Chromosome&) const;
};


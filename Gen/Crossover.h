#pragma once

#include "Chromosome.h"


class Crossover
{
public:
	virtual ~Crossover() {};

	virtual void operator()(Chromosome&, const Chromosome&, const Chromosome&) = 0;
};

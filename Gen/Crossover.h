#pragma once

#include "Chromosome.h"


class Crossover
{
public:
	virtual ~Crossover() {};

	virtual Chromosome* operator()(const Chromosome&, const Chromosome&) = 0;
};

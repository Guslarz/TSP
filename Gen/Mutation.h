#pragma once

#include "Chromosome.h"


class Mutation
{
public:
	virtual ~Mutation() {};

	virtual Chromosome* operator()(const Chromosome&) = 0;
};


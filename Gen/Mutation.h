#pragma once

#include "Chromosome.h"


class Mutation
{
public:
	virtual ~Mutation() {};

	virtual void operator()(Chromosome&, const Chromosome&) = 0;
};


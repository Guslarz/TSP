#pragma once

#include "Mutation.h"


class ReverseSequenceMutation : 
	public Mutation
{
	const size_t n;
	randgen_t &randomGenerator;
	const std::uniform_int_distribution<size_t> distribution;

public:
	ReverseSequenceMutation(const size_t, randgen_t&);
	~ReverseSequenceMutation();

	void operator()(Chromosome&, const Chromosome&);
};


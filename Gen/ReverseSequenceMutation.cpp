#include "ReverseSequenceMutation.h"


ReverseSequenceMutation::ReverseSequenceMutation(const size_t n, randgen_t &randomGenerator) :
	n(n),
	randomGenerator(randomGenerator),
	distribution(0, n - 1)
{}


ReverseSequenceMutation::~ReverseSequenceMutation()
{}


Chromosome* ReverseSequenceMutation::operator()(const Chromosome &chromosome)
{
	auto newChromosome = new Chromosome(chromosome);
	auto &genome = newChromosome->getGenome();

	size_t i = distribution(randomGenerator), j;
	while ((j = distribution(randomGenerator)) == i);
	if (i > j) std::swap(i, j);

	while (i < j)
		std::swap(genome[i++], genome[j--]);

	return newChromosome;
}

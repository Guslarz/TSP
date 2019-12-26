#include "ReverseSequenceMutation.h"


ReverseSequenceMutation::ReverseSequenceMutation(const size_t n, randgen_t &randomGenerator) :
	n(n),
	randomGenerator(randomGenerator),
	distribution(1, n - 1)
{}


ReverseSequenceMutation::~ReverseSequenceMutation()
{}


void ReverseSequenceMutation::operator()(Chromosome &mutated, const Chromosome &initial)
{
	auto &mutatedGenome = mutated.getGenome();
	auto &initialGenome = initial.getGenome();

	size_t i = distribution(randomGenerator), j;
	while ((j = distribution(randomGenerator)) == i);
	if (i > j) std::swap(i, j);

	size_t index = 0;
	while (index < i) {
		mutatedGenome[index] = initialGenome[index];
		++index;
	}
	while (j >= i)
		mutatedGenome[index++] = initialGenome[j--];
	while (index < n) {
		mutatedGenome[index] = initialGenome[index];
		++index;
	}
}

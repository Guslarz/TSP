#include "Chromosome.h"



Chromosome::Chromosome(const size_t n) :
	genome(std::make_unique<genome_t>(n))
{}


Chromosome::Chromosome(const Chromosome &other) :
	Chromosome(other.genome->size())
{
	const size_t n = other.genome->size();
	for (size_t i = 0; i < n; ++i)
		(*genome)[i] = other.genome->at(i);
}


Chromosome::~Chromosome()
{}


std::ostream& operator<<(std::ostream &out, const Chromosome &chromosome)
{
	for (auto gene : *chromosome.genome)
		out << gene << " ";
	out << chromosome.genome->front();
	return out;
}
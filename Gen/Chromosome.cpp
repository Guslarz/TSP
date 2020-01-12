#include "Chromosome.h"



Chromosome::Chromosome(const size_t n) :
	genome(n)
{}


Chromosome::Chromosome(const Chromosome &other) :
	Chromosome(other.genome.size())
{
	const size_t n = other.genome.size();
	for (size_t i = 0; i < n; ++i)
		genome[i] = other.genome.at(i);
}


Chromosome::~Chromosome()
{}


void Chromosome::setFitness(const distarr_t &distance)
{
	const size_t n = genome.size();
	fitness = distance[genome[n - 1]][genome[0]];
	for (size_t i = 1; i < n; ++i)
		fitness += distance[genome[i - 1]][genome[i]];
}


std::ostream& operator<<(std::ostream &out, const Chromosome &chromosome)
{
	for (auto gene : chromosome.genome)
		out << gene << " ";
	out << chromosome.genome.front() << " " << chromosome.fitness;
	return out;
}


void Chromosome::printRepresentation(std::ostream &out, const Instance &instance) const
{
	for (auto &gene : genome)
		out << instance.getCity(gene) << " ";
	out << instance.getCity(genome[0]);
}
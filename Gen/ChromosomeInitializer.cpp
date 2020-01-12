#include "ChromosomeInitializer.h"



ChromosomeInitializer::ChromosomeInitializer(const size_t n, const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator),
	index(1),
	improvedLimit(1000000 / (n * n)),
	greedyChromosomes(n - 1)
{
	for (auto &chromosome : greedyChromosomes) {
		chromosome = std::make_unique<Chromosome>(n);
		greedyInitialize(*chromosome);
		++index;
	}
	index = 0;
	std::sort(greedyChromosomes.begin(), greedyChromosomes.end(), &Chromosome::compare);
}


ChromosomeInitializer::~ChromosomeInitializer()
{}


chromosomeptr_t ChromosomeInitializer::operator()()
{
	chromosomeptr_t chromosome;
	if (index < n - 1)
		chromosome.swap(greedyChromosomes[index]);
	else {
		chromosome = std::make_unique<Chromosome>(n);
		randomInitialize(*chromosome);
	}
	if (index < improvedLimit) 
		improve(*chromosome);
	++index;
	return chromosome;
}


void ChromosomeInitializer::randomInitialize(Chromosome &chromosome) const
{
	auto &genome = chromosome.getGenome();
	for (size_t i = 0; i < n; ++i)
		genome[i] = i;
	std::shuffle(genome.begin() + 1, genome.end(), randomGenerator);
}


void ChromosomeInitializer::greedyInitialize(Chromosome &chromosome) const
{
	auto &genome = chromosome.getGenome();
	size_t i, j, current = index, next, firstNotVisited = 0;
	std::vector<bool> visited(n);

	visited[0] = true;
	genome[0] = 0;
	visited[current] = true;
	genome[1] = current;
	for (i = 2; i < n; ++i) {
		while (visited[firstNotVisited]) ++firstNotVisited;
		next = firstNotVisited;

		for (j = next + 1; j < n; ++j)
			if (!visited[j] && distance[current][j] < distance[current][next])
				next = j;

		current = next;
		genome[i] = current;
		visited[current] = true;
	}
}


void ChromosomeInitializer::improve(Chromosome &chromosome) const
{
	auto &genome = chromosome.getGenome();
	fitness_t currentFitness = chromosome.getFitness();

	for (size_t i = 1; i < n; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			std::swap(genome[i], genome[j]);
			chromosome.setFitness(distance);
			if (chromosome.getFitness() < currentFitness) {
				currentFitness = chromosome.getFitness();
			}
			else {
				std::swap(genome[i], genome[j]);
				chromosome.setFitness(distance);
			}
		}
	}
}
#include "ChromosomeInitializer.h"



ChromosomeInitializer::ChromosomeInitializer(const size_t n, const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator),
	first(0)
{}


ChromosomeInitializer::~ChromosomeInitializer()
{}


Chromosome* ChromosomeInitializer::operator()()
{
	auto chromosome = new Chromosome(n);
	if (first == n) {
		randomInitialize(*chromosome);
	}
	else {
		greedyInitialize(*chromosome);
		++first;
	}
	return chromosome;
}


void ChromosomeInitializer::randomInitialize(Chromosome &chromosome) const
{
	auto &genome = chromosome.getGenome();
	for (size_t i = 0; i < n; ++i)
		genome[i] = i;
	std::shuffle(genome.begin(), genome.end(), randomGenerator);
}


void ChromosomeInitializer::greedyInitialize(Chromosome &chromosome) const
{
	size_t i, j, next, current = first, firstNotVisited = 0;
	auto &genome = chromosome.getGenome();
	bool *visited = new bool[n];
	for (i = 0; i < n; ++i)
		visited[i] = false;

	visited[current] = true;
	genome[0] = current;

	for (i = 1; i < n; ++i) {
		while (visited[firstNotVisited]) ++firstNotVisited;
		next = firstNotVisited;

		for (j = next + 1; j < n; ++j) {
			if (!visited[j] && distance[current][next] > distance[current][j])
				next = j;
		}
		
		current = next;
		visited[current] = true;
		genome[i] = current;
	}

	delete[] visited;
}
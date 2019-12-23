#include "SequentialConsecutiveCrossover.h"


SequentialConsecutiveCrossover::SequentialConsecutiveCrossover(const size_t n, 
	const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator)
{}


SequentialConsecutiveCrossover::~SequentialConsecutiveCrossover()
{}


Chromosome* SequentialConsecutiveCrossover::operator()(const Chromosome &parent1, 
	const Chromosome &parent2)
{
	bool *visited = new bool[n];
	gene_t *next1 = new gene_t[n],
		*next2 = new gene_t[n];
	size_t i;
	gene_t current = 0, firstNotVisited = 0, tmp1, tmp2;
	auto child = new Chromosome(n);
	auto &childGenome = child->getGenome();
	auto &parent1Genome = parent1.getGenome(),
		&parent2Genome = parent2.getGenome();

	for (i = 0; i < n; ++i) {
		visited[i] = false;
		if (i == n - 1) {
			next1[parent1Genome[i]] = parent1Genome[0];
			next2[parent2Genome[i]] = parent2Genome[0];
		}
		else {
			next1[parent1Genome[i]] = parent1Genome[i + 1];
			next2[parent2Genome[i]] = parent2Genome[i + 1];
		}
	}

	visited[current] = true;
	childGenome[0] = current;

	for (i = 1; i < n; ++i) {
		tmp1 = next1[current];
		if (visited[tmp1]) {
			while (visited[firstNotVisited]) ++firstNotVisited;
			tmp1 = firstNotVisited;
		}
		tmp2 = next2[current];
		if (visited[tmp2]) {
			while (visited[firstNotVisited]) ++firstNotVisited;
			tmp2 = firstNotVisited;
		}

		current = distance[current][tmp1] < distance[current][tmp2] ?
			tmp1 : tmp2;
		visited[current] = true;
		childGenome[i] = current;
	}

	delete[] visited, next1, next2;
	return child;
}
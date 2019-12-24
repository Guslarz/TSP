#include "ChromosomeInitializer.h"



ChromosomeInitializer::ChromosomeInitializer(const size_t n, const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator),
	first(0)
{}


ChromosomeInitializer::~ChromosomeInitializer()
{}


chromosomeptr_t ChromosomeInitializer::operator()()
{
	auto chromosome = std::make_unique<ChromosomeAsEdges>(n);
	if (first == n)
		randomInitialize(*chromosome);
	else {
		greedyInitialize(*chromosome);
		++first;
	}
	return fromEdges(*chromosome);
}


void ChromosomeInitializer::randomInitialize(ChromosomeAsEdges &chromosome) const
{
	std::vector<gene_t> genome(n);
	for (size_t i = 0; i < n; ++i)
		genome[i] = i;
	std::shuffle(genome.begin(), genome.end(), randomGenerator);

	for (auto it1 = genome.begin(), it2 = genome.end() - 1; it1 != genome.end(); it2 = it1++)
		chromosome.addEdge({ *it1, *it2, distance });
}


void ChromosomeInitializer::greedyInitialize(ChromosomeAsEdges &chromosome) const
{
	size_t i, j, current = first, next, firstNotVisited = 0;
	std::vector<bool> visited(n);

	visited[current] = true;
	for (i = 1; i < n; ++i) {
		while (visited[firstNotVisited]) ++firstNotVisited;
		next = firstNotVisited;

		for (j = next + 1; j < n; ++j)
			if (!visited[j] && distance[current][j] < distance[current][next])
				next = j;

		chromosome.addEdge({ current, next, distance });
		current = next;
		visited[current] = true;
	}
	chromosome.addEdge({ current, first, distance });
}


void ChromosomeInitializer::apply4Perm(ChromosomeAsEdges &initial) const
{
	//std::shared_ptr<ChromosomeAsEdges> initialptr = &initial;
}


chromosomeptr_t ChromosomeInitializer::fromEdges(const ChromosomeAsEdges &chromosome) const
{
	auto newChromosome = std::make_unique<Chromosome>(n);
	auto &genome = newChromosome->getGenome();
	auto &edges = chromosome.getEdges();
	std::vector<bool> visited(n, false);
	size_t i, current = 0, next;

	visited[current] = true;
	genome[0] = current;

	for (i = 1; i < n; ++i) {
		next = 1;
		while (visited[next] || !edges[current][next]) ++next;

		current = next;
		visited[current] = true;
		genome[i] = current;
	}

	return newChromosome;
}
#include "Population.h"



Population::Population(const size_t n, const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator),
	distribution(0, BREEDING_POOL_SIZE - 1),
	chromosomeInitializer(std::make_unique<ChromosomeInitializer>(n, distance, randomGenerator)),
	mutation(std::make_unique<ReverseSequenceMutation>(n, randomGenerator)),
	crossover(std::make_unique<SequentialConsecutiveCrossover>(n, distance, randomGenerator)),
	bestFitness(0)
{
	for (auto &chromosome : chromosomes) {
		chromosome = chromosomeptr_t((*chromosomeInitializer)());
		setFitness(*chromosome);
	}
	evaluate();
}


Population::~Population()
{}


void Population::nextGeneration()
{
	bestFitness = chromosomes[0]->getFitness();
	fillBreedingPool();
	breed();
	mutate();
	elite();
	evaluate();
}


void Population::setFitness(Chromosome &chromosome)
{
	auto &genome = chromosome.getGenome();
	fitness_t fitness = distance[genome[n - 1]][genome[0]];
	for (size_t i = 1; i < n; ++i)
		fitness += distance[genome[i - 1]][genome[i]];
	chromosome.setFitness(fitness);
}


void Population::evaluate()
{
	std::sort(chromosomes.begin(), chromosomes.end(), &compareFitness);
}


void Population::fillBreedingPool()
{
	size_t i = 0, j = 0;
	while (i < FITTEST)
		breedingPool[i++] = std::move(chromosomes[j++]);
	j += GAP_SIZE;
	while (i < FITTEST + MIDDLE)
		breedingPool[i++] = std::move(chromosomes[j++]);
	j += GAP_SIZE;
	while (i < BREEDING_POOL_SIZE)
		breedingPool[i++] = std::move(chromosomes[j++]);
}


void Population::breed()
{
	size_t index1, index2;
	for (size_t i = 0; i < OFFSPRING_COUNT; ++i) {
		index1 = distribution(randomGenerator);
		while ((index2 = distribution(randomGenerator)) == index1);

		chromosomes[i] = chromosomeptr_t((*crossover)(*breedingPool[index1], *breedingPool[index2]));
		setFitness(*chromosomes[i]);
	}
}


void Population::mutate()
{
	size_t index;
	for (size_t i = 0; i < MUTANTS_COUNT; ++i) {
		index = distribution(randomGenerator);

		chromosomes[OFFSPRING_COUNT + i] = chromosomeptr_t((*mutation)(*breedingPool[index]));
		setFitness(*chromosomes[OFFSPRING_COUNT + i]);
	}
}


void Population::elite()
{
	for (size_t i = 0; i < ELITE_COUNT; ++i)
		chromosomes[OFFSPRING_COUNT + MUTANTS_COUNT + i] = std::move(breedingPool[i]);
}


std::ostream& operator<<(std::ostream &out, const Population &population)
{
	for (auto &chromosome : population.chromosomes)
		out << chromosome->getFitness() << "\n";
	return out;
}


bool compareFitness(const chromosomeptr_t &l, const chromosomeptr_t &r)
{
	return l->getFitness() < r->getFitness();
}
#include "Population.h"



Population::Population(const size_t n, const distarr_t &distance, randgen_t &randomGenerator) :
	n(n),
	distance(distance),
	randomGenerator(randomGenerator),
	distribution(0, BREEDING_POOL_SIZE - 1),
	mutation(std::make_unique<ReverseSequenceMutation>(n, randomGenerator)),
	crossover(std::make_unique<SequentialConsecutiveCrossover>(n, distance, randomGenerator)),
	change(true)
{
	std::cout << "Generowanie populacji" << std::endl;

	auto chromosomeInitializer = std::make_unique<ChromosomeInitializer>(n, distance, randomGenerator);

	for (auto &chromosome : chromosomes) {
		chromosome = (*chromosomeInitializer)();
		chromosome->setFitness(distance);
	}
	bestFitness = chromosomes.front()->getFitness();
	evaluate();
	for (auto &chromosome : breedingPool)
		chromosome = std::make_unique<Chromosome>(n);
}


Population::~Population()
{}


void Population::nextGeneration()
{
	fillBreedingPool();
	breed();
	mutate();
	elite();
	evaluate();
}


const Chromosome& Population::getBest() const
{
	size_t best = 0, i = 1;
	while (i < POPULATION_SIZE) {
		if (chromosomes[i]->getFitness() < chromosomes[best]->getFitness())
			best = i;
		++i;
	}
	return *chromosomes[best];
}


void Population::evaluate()
{
	std::sort(chromosomes.begin(), chromosomes.end(), &Chromosome::compare);
	auto tmp = chromosomes[0]->getFitness();
	if ((bestFitness - tmp) / tmp >= MINIMUM_CHANGE_PERC) {
		change = true;
		bestFitness = tmp;
	}
	else change = false;
}


void Population::fillBreedingPool()
{
	size_t i = 0, j = 0;
	while (i < FITTEST)
		breedingPool[i++].swap(chromosomes[j++]);
	j += GAP_SIZE;
	while (i < FITTEST + MIDDLE)
		breedingPool[i++].swap(chromosomes[j++]);
	j += GAP_SIZE;
	while (i < BREEDING_POOL_SIZE)
		breedingPool[i++].swap(chromosomes[j++]);
}


void Population::breed()
{
	size_t index1, index2;
	float random1, random2;
	for (size_t i = 0; i < OFFSPRING_COUNT; ++i) {
		random1 = std::generate_canonical<float, 3>(randomGenerator);
		index2 = index1 = static_cast<size_t>(std::pow(random1, PARENT_INDEX_EXP) * BREEDING_POOL_SIZE);
		while (index2 == index1) {
			random2 = std::generate_canonical<float, 3>(randomGenerator);
			index2 = static_cast<size_t>(std::pow(random2, PARENT_INDEX_EXP) * BREEDING_POOL_SIZE);
		}

		(*crossover)(*chromosomes[i], *breedingPool[index1], *breedingPool[index2]);
		chromosomes[i]->setFitness(distance);
	}
}


void Population::mutate()
{
	size_t index;
	for (size_t i = 0; i < MUTANTS_COUNT; ++i) {
		index = distribution(randomGenerator);
		(*mutation)(*chromosomes[OFFSPRING_COUNT + i] , *breedingPool[index]);
		chromosomes[OFFSPRING_COUNT + i]->setFitness(distance);
	}
}


void Population::elite()
{
	for (size_t i = 0; i < ELITE_COUNT; ++i)
		chromosomes[OFFSPRING_COUNT + MUTANTS_COUNT + i].swap(breedingPool[i]);
}


std::ostream& operator<<(std::ostream &out, const Population &population)
{
	for (auto &chromosome : population.chromosomes)
		out << *chromosome << "\n";
		//out << chromosome->getFitness() << "\n";
	std::cout << "---\n";
	for (auto &chromosome : population.breedingPool)
		out << *chromosome << "\n";
	return out;
}
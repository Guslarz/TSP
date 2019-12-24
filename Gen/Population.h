#pragma once

#include "ChromosomeInitializer.h"
#include "ReverseSequenceMutation.h"
#include "SequentialConsecutiveCrossover.h"

#include <array>


constexpr size_t
POPULATION_SIZE = 52,
//selection
FITTEST = static_cast<size_t>(0.5 * POPULATION_SIZE),
MIDDLE = static_cast<size_t>(0.2 * POPULATION_SIZE),
WORST = static_cast<size_t>(0.1 * POPULATION_SIZE),
BREEDING_POOL_SIZE = FITTEST + MIDDLE + WORST,
GAP_SIZE = (POPULATION_SIZE - BREEDING_POOL_SIZE) / 2,
//elite
ELITE_COUNT = 1;

//breeding and mutation
constexpr float
MUTATION_CHANCE = 0.1f;
constexpr size_t
MUTANTS_COUNT = static_cast<size_t>(MUTATION_CHANCE * POPULATION_SIZE),
OFFSPRING_COUNT = POPULATION_SIZE - ELITE_COUNT - MUTANTS_COUNT;


class Population
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

	std::uniform_int_distribution<size_t> distribution;

	const std::unique_ptr<ChromosomeInitializer> chromosomeInitializer;
	const std::unique_ptr<Mutation> mutation;
	const std::unique_ptr<Crossover> crossover;

	std::array<chromosomeptr_t, POPULATION_SIZE> chromosomes;
	std::array<chromosomeptr_t, BREEDING_POOL_SIZE> breedingPool;

	fitness_t bestFitness;
	bool change;

public:
	Population(const size_t, const distarr_t&, randgen_t&);
	~Population();

	void nextGeneration();
	bool hasChanged() const { return change; }
	const Chromosome& getBest() const;

	friend std::ostream& operator<<(std::ostream&, const Population&);

private:
	void evaluate();
	void fillBreedingPool();
	void breed();
	void mutate();
	void elite();
};


std::ostream& operator<<(std::ostream&, const Population&);
bool compareFitness(const chromosomeptr_t&, const chromosomeptr_t&);


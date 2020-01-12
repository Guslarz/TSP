#pragma once

#include "ChromosomeInitializer.h"
#include "ReverseSequenceMutation.h"
#include "SequentialConsecutiveCrossover.h"

#include <array>


constexpr size_t
POPULATION_SIZE = 250,
//selection
FITTEST = static_cast<size_t>(0.4 * POPULATION_SIZE),
MIDDLE = static_cast<size_t>(0.1 * POPULATION_SIZE),
WORST = static_cast<size_t>(0.05 * POPULATION_SIZE),
BREEDING_POOL_SIZE = FITTEST + MIDDLE + WORST,
GAP_SIZE = (POPULATION_SIZE - BREEDING_POOL_SIZE) / 2,
//elite
ELITE_COUNT = 10;

//breeding and mutation
constexpr float
MUTATION_CHANCE = 0.3f;
constexpr size_t
MUTANTS_COUNT = static_cast<size_t>(MUTATION_CHANCE * POPULATION_SIZE),
OFFSPRING_COUNT = POPULATION_SIZE - ELITE_COUNT - MUTANTS_COUNT;
constexpr double
PARENT_INDEX_EXP = 10,
MINIMUM_CHANGE_PERC = 0.001;


class Population
{
	const size_t n;
	const distarr_t &distance;
	randgen_t &randomGenerator;

	std::uniform_int_distribution<size_t> distribution;

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

	void printRepresentation(std::ostream &out, const Instance &instance) { getBest().printRepresentation(out, instance); out << std::endl; }

	friend std::ostream& operator<<(std::ostream&, const Population&);
	friend class Solution;

private:
	void evaluate();
	void fillBreedingPool();
	void breed();
	void mutate();
	void elite();
};


std::ostream& operator<<(std::ostream&, const Population&);


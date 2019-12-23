#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <random>


using gene_t = size_t;
using fitness_t = double;
using genome_t = std::vector<gene_t>;
using distarr_t = std::vector<std::vector<fitness_t>>;
using randgen_t = std::mt19937;


class Chromosome
{
	const std::unique_ptr<genome_t> genome;
	fitness_t fitness;

public:
	Chromosome(const size_t);
	Chromosome(const Chromosome&);
	~Chromosome();

	genome_t& getGenome() { return *genome; }
	const genome_t& getGenome() const { return *genome; }
	fitness_t getFitness() const { return fitness; }

	void setFitness(fitness_t value) { fitness = value; }

	friend std::ostream& operator<<(std::ostream&, const Chromosome&);
};


using chromosomeptr_t = std::unique_ptr<Chromosome>;


std::ostream& operator<<(std::ostream&, const Chromosome&);
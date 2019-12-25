#pragma once

#include "Instance.h"
#include "Population.h"
#include "Result.h"


constexpr unsigned int
MIN_GENERATIONS = 1000,
GENERATIONS_DENOMINATOR = 2;


class Solution
{
	const std::unique_ptr<const Instance> instance;
	const size_t n;
	const std::unique_ptr<const distarr_t> distance;
	const std::unique_ptr<randgen_t> randomGenerator;
	const std::unique_ptr<Population> population;
	timepoint_t start, stop;
	std::unique_ptr<Result> result;
	unsigned int generationCounter, noChangeCounter;

	static std::random_device rd;

public:
	Solution(const std::string&);
	~Solution();

	const Result& getResult() const { return *result; }

private:
	distarr_t* getDistanceArray() const;
	void runGeneticAlgorithm();
	bool shouldContinue() const;
	void updateCounters();
};


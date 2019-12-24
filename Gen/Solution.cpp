#include "Solution.h"


std::random_device Solution::rd;


Solution::Solution(const std::string &filename) :
	start(std::chrono::high_resolution_clock::now()), 
	instance(std::make_unique<const Instance>(filename)),
	n(instance->getN()),
	distance(getDistanceArray()),
	randomGenerator(std::make_unique<randgen_t>(rd())),
	population(std::make_unique<Population>(n, *distance, *randomGenerator))
{
	runGeneticAlgorithm();
	stop = std::chrono::high_resolution_clock::now();
	result = std::make_unique<Result>(n, generationCounter, population->getBest(), stop - start);
}


Solution::~Solution()
{}
	

distarr_t* Solution::getDistanceArray() const
{
	auto &points = instance->getPoints();
	distarr_t *distanceArray = new distarr_t(n);
	size_t i, j;

	for (i = 0; i < n; ++i)
		(*distanceArray)[i].resize(n);

	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j)
			(*distanceArray)[i][j] = (*distanceArray)[j][i] = points[i].distance(points[j]);
	}

	return distanceArray;
}


void Solution::runGeneticAlgorithm()
{
	while (shouldContinue()) {
		population->nextGeneration();
		updateCounters();
	}
}


bool Solution::shouldContinue() const
{
	return noChangeCounter < std::max(MIN_GENERATIONS, generationCounter / GENERATIONS_DENOMINATOR);
}


void Solution::updateCounters()
{
	if (population->hasChanged()) 
		noChangeCounter = 0;
	++generationCounter;
	++noChangeCounter;
}
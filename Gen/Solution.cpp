#include "Solution.h"

#include <fstream>


std::random_device Solution::rd;


Solution::Solution(const std::string &filename) :
	start(std::chrono::high_resolution_clock::now()), 
	instance(std::make_unique<const Instance>(filename)),
	n(instance->getN()),
	distance(getDistanceArray()),
	randomGenerator(std::make_unique<randgen_t>(rd())),
	population(std::make_unique<Population>(n, *distance, *randomGenerator))
{
	std::cout << "Start" << std::endl;

	runGeneticAlgorithm();
	stop = std::chrono::high_resolution_clock::now();

	std::cout << "Stop" << std::endl;

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
	/*std::fstream out("out.txt", std::ios::out);
	population->printRepresentation(out, *instance);*/

	while (shouldContinue()) {
		population->nextGeneration();
		updateCounters();

		/*if (generationCounter == 100)
			population->printRepresentation(out, *instance);*/
	}

	/*population->printRepresentation(out, *instance);
	out.close();*/

	std::fstream out("out.txt", std::ios::out);
	Chromosome c1(population->getBest()), c2(c1), c3(c1), c4(c1), c5(c1);
	c1.printRepresentation(out, *instance);
	out << std::endl;
	(*population->mutation)(c2, c1);
	c2.printRepresentation(out, *instance);
	out << std::endl;
	auto &g3 = c3.getGenome(), &g4 = c4.getGenome();
	std::swap(g3[0], g3[1]);
	std::swap(g4[6], g4[7]);
	(*population->crossover)(c5, c3, c4);
	c3.printRepresentation(out, *instance);
	out << std::endl;
	c4.printRepresentation(out, *instance);
	out << std::endl;
	c5.printRepresentation(out, *instance);
	out << std::endl;

	out.close();
}


bool Solution::shouldContinue() const
{
	return noChangeCounter < std::max(MIN_GENERATIONS, generationCounter / GENERATIONS_DENOMINATOR);
}


void Solution::updateCounters()
{
	if (population->hasChanged()) {
		std::cout << generationCounter << std::endl;
		noChangeCounter = 0;
	}
	++generationCounter;
	++noChangeCounter;
}
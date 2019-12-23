#include "Result.h"



Result::Result(const size_t n, const Chromosome &chromosome, const duration_t duration) :
	n(n),
	chromosome(std::move(chromosome)),
	duration(duration)
{}


Result::~Result()
{}


std::ostream& operator<<(std::ostream &out, const Result &result)
{
	out << "Algorytm genetyczny\n";
	out << "Liczba wierzcholkow: " << result.n << "\n";
	out << "Dystans: " << result.chromosome.getFitness() << "\n";
	out << "Czas: " << result.duration.count() << " s\n";
	return out;
}
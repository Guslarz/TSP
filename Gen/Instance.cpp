#include "Instance.h"

#include <fstream>
#include <random>



Instance::Instance(std::istream &in)
{
	*this << in;
}


Instance::Instance(const std::string &filename)
{
	std::fstream in(filename, std::ios::in);
	*this << in;
	in.close();
}


Instance::~Instance()
{}


void Instance::generate(const std::string &filename, const size_t n, const int limit)
{
	std::fstream f(filename, std::ios::out);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, limit);

	f << n << std::endl;
	for (size_t i = 0; i < n; ++i) {
		f << i + 1 << " ";
		f << dis(gen) << " ";
		f << dis(gen) << std::endl;
	}

	f.close();
}


std::ostream& operator<<(std::ostream &out, const Instance &instance)
{
	out << instance.getN() << "\n";
	for (auto &point : instance.getPoints())
		out << point << "\n";
	return out;
}


void Instance::operator<<(std::istream &in)
{
	size_t n;
	in >> n;

	for (size_t i = 0; i != n; ++i)
		points.emplace_back(in);
}
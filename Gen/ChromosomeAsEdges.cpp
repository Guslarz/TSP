#include "ChromosomeAsEdges.h"



ChromosomeAsEdges::ChromosomeAsEdges(const size_t n) :
	edge(n),
	fitness(0)
{
	for (auto &vec : edge)
		vec.resize(n, false);
}


ChromosomeAsEdges::ChromosomeAsEdges(const ChromosomeAsEdges &other) :
	edge(other.edge.size()),
	fitness(other.fitness)
{
	const size_t n = other.edge.size();
	for (size_t i = 0; i < n; ++i)
		edge[i] = other.edge.at(i);
}


ChromosomeAsEdges::~ChromosomeAsEdges()
{}


void ChromosomeAsEdges::addEdge(const Edge &e)
{
	edge[e.a][e.b] = edge[e.b][e.a] = true;
	fitness += e.fitness;
}


void ChromosomeAsEdges::removeEdge(const Edge &e)
{
	edge[e.a][e.b] = edge[e.b][e.a] = false;
	fitness -= e.fitness;
}
#pragma once

#include "Chromosome.h"


struct Edge
{
	gene_t a, b;
	fitness_t fitness;

	Edge(const gene_t a, const gene_t b, const fitness_t fitness) :
		a(a), b(b), fitness(fitness) {}
	Edge(const gene_t a, const gene_t b, const distarr_t &distance) :
		Edge(a, b, distance[a][b]) {}

	bool hasVertex(const gene_t vertex) const { return a == vertex || b == vertex; }
	bool hasCommonCity(const Edge &edge) const { return hasVertex(edge.a) || hasVertex(edge.b); }

	bool operator>(const Edge &other) const { return fitness > other.fitness; }
};


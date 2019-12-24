#pragma once

#include "Chromosome.h"


struct Edge
{
	const gene_t a, b;
	const fitness_t fitness;

	Edge(const gene_t a, const gene_t b, const fitness_t fitness) :
		a(a), b(b), fitness(fitness) {}
	Edge(const gene_t a, const gene_t b, const distarr_t &distance) :
		Edge(a, b, distance[a][b]) {}

	bool hasVertex(const gene_t vertex) const { return a == vertex || b == vertex; }
	bool hasCommonCity(const Edge &edge) const { return hasVertex(edge.a) || hasVertex(edge.b); }

	static bool compare(const Edge &l, const Edge&r) { return l.fitness > r.fitness; }
};


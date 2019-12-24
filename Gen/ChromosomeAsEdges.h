#pragma once

#include "Edge.h"


using edgearr_t = std::vector<std::vector<bool>>;

class ChromosomeAsEdges
{
	edgearr_t edge;
	fitness_t fitness;

public:
	ChromosomeAsEdges(const size_t);
	ChromosomeAsEdges(const ChromosomeAsEdges&);
	~ChromosomeAsEdges();

	bool hasEdge(const Edge &e) const { return edge[e.a][e.b]; }
	bool hasEdge(const gene_t a, const gene_t b) const { return edge[a][b]; }

	void addEdge(const Edge &e);
	void removeEdge(const Edge &e);

	edgearr_t& getEdges() { return edge; }
	const edgearr_t& getEdges() const { return edge; }
};


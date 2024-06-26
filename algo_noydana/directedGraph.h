#pragma once

#include <iostream>
#include <list>
#include <stdlib.h>
#include <vector>
#include "vertex.h"
#include "exceptions.h"

using namespace std;


class DirectedGraph
{
	int verticesNumber;
	int edgesNumber;
	vector<vertex> vertices;

public:
	DirectedGraph(int verticesNumber = 0, int edgesNumber = 0);
	enum class colors { white, gray, black };
	int getVerticesNumber() const;
	int getEdgesNumber() const;
	void MakeEmptyGraph(int n);
	bool IsAdjacent(int u, int v);
	list<int> GetAdjList(int u);
	void AddEdge(int u, int v);
	void RemoveEdge(int u, int v);
	void checkValidEdge(int u, int v);
	DirectedGraph makeSuperGraph();
	void checkAdjListAndAddToGraph(DirectedGraph& superGraph, DirectedGraph& tempGraph);
	void checkIfNewRoot(DirectedGraph& tempGraph, vector<int>& roots, int v);
	~DirectedGraph() {};


private:
	list<int> DFS(list<int> mainLoop, DirectedGraph& superGraph);
	DirectedGraph transposedGraph();
	void visit(int u, vector<DirectedGraph::colors>& colors, vector<int>& roots, list<int>& finishLoop, DirectedGraph& tempGraph);

};


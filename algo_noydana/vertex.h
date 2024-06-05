
#pragma once
#include <iostream>
#include <list>
using namespace std;

class vertex
{
	int value;
	list<int> adjList;

public:
	vertex(int value, list<int> adjList) : value(value), adjList(adjList) {}
	vertex(int value) : value(value) {
		adjList.empty();
	}
	int getValue() const { return value; }
	list<int>& getAdjList() { return adjList; }
	void setValue(int val) { value = val; }
};

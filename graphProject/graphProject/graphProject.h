#pragma once
#define NDEBUG

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <iterator>
#include <cassert>
#include <queue>
using namespace std;



template <class T>
class Graph {
public:
	virtual bool adjacent(T, T) = 0;
	virtual vector <int> neighbors(T)=0;
	virtual void addEdge(T, T) = 0;
	virtual void deleteEdge(T, T) = 0;
	virtual void deleteNode(T) = 0;

private:
};







template <class T>
class AdjacencyMatrixGraph : public Graph<T> {
public:
	bool adjacent(T, T);
    vector <int> neighbors(T);
	int ** generateNewGraph(int, double);
	void displayMatrixGraph();
	void addEdge(T, T);
	void deleteEdge(T, T);
	void deleteNode(T);
	void bfs(AdjacencyMatrixGraph&, T);
	void visit(T);

	void getVertexNumber(vector<T>&, vector<bool>&, queue<T>&);
	
private:
	T **adjMatrixArray;
	int size = 0;

};

#include "graphProject.hxx"

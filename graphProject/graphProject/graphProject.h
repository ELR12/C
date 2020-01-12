#pragma once
#define NDEBUG

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <iterator>
using namespace std;



template <class T>
class Graph {
public:
	virtual bool adjacent(T, T) = 0;
	virtual vector <int> neighbors(T)=0;

private:
};







template <class T>
class AdjacencyMatrixGraph : public Graph<T> {
public:
	bool adjacent(T, T);
    vector <int> neighbors(T);
	int ** generateNewGraph(int, double);
	void displayMatrixGraph();
private:
	T **adjMatrixArray;
	int size = 0;

};

#include "graphProject.hxx"
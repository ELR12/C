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
#include <list>
using namespace std;

const int SET_SIZE = 10;



template <class T>
class Graph 
{
public:
	Graph();
	~Graph();
	virtual bool adjacent(T, T) = 0;
	virtual vector <int> neighbors(T)=0;
	virtual void addEdge(T, T) = 0;
	virtual void deleteEdge(T, T) = 0;
	virtual void deleteNode(T) = 0;
private:
};





template <class T>
class AdjacencyMatrixGraph : public Graph<T> 
{
public:
	AdjacencyMatrixGraph();
	~AdjacencyMatrixGraph();
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
	int size;
};






template <class T>
class AdjacencyListGraph : public Graph<T>
{
	public:
		AdjacencyListGraph();
		~AdjacencyListGraph();
		bool adjacent(T, T);
		vector <int> neighbors(T);
		void addEdge(T, T);
		void deleteEdge(T, T);
		void deleteNode(T);
		void  generateNewGraph(int,double);
		void displayListGraph();

	private:
		list<T> myList[SET_SIZE];
		list<int>::iterator listIter;
		int size;
};




#include "graphProject.hxx"

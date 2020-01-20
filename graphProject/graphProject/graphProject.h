/*
Created by
Ethan Roberts
on 01/10/2020

This program creates an ADT of a Graph.  "MatrixGraph" and "ListGraph" will be implemented.

cite:  https://www.geeksforgeeks.org/set-find-function-in-c-stl/  (for learning how to use a "Set" container
cite:  http://www.cplusplus.com/reference/list/list/

*/





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
	Graph& generateNewGraph(int,double);
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
	AdjacencyMatrixGraph& generateNewGraph(int, double);
	void displayMatrixGraph();
	void addEdge(T, T);
	void deleteEdge(T, T);
	void deleteNode(T);
	void bfs(AdjacencyMatrixGraph&, T&);
	void visit(T);
	void getVertexNumber(vector<T>&, vector<bool>&, queue<T>&);
	void dfs(AdjacencyMatrixGraph&, T&);
	void dfsHelper(AdjacencyMatrixGraph&, T, vector<bool>&, int);
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
		AdjacencyListGraph& generateNewGraph(int,double);
		void displayListGraph();
		void bfs(AdjacencyListGraph&, T&);
		void visit(T);
		void dfs(AdjacencyListGraph&, T&);
		void dfsHelper(AdjacencyListGraph&, T, vector<bool>&, int);
	private:
		list<T> myList[SET_SIZE];
		list<int>::iterator listIter;
		int size;
};




#include "graphProject.hxx"

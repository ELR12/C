/*
	Created by
	Ethan Roberts
	on 01/10/2019

	This program creates a graph adt.
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <list>
#include <algorithm> //for using find() method

using namespace std;

static const int SIZE = 10;

//the Graph class is a pure virtual class
template <class T>
class Graph {
public:
	Graph();
	~Graph();
	virtual bool adjacent(T, T)= 0;
	virtual void addEdge(T, T) = 0;
	virtual void deleteNode(T) = 0;
	virtual void deleteEdge(T, T) = 0;
	virtual vector <T> neighbors(T) = 0;
	void dfs(Graph<T>&, T, bool[]);
	void dfsHelper(T);
	void bfs(Graph<T>&, T, T);
	void clearGraph();


private:

};










//Using 2D-array for Adjacency Matrix representation
template <class T>
class AdjMatrixGraph : public Graph<T> {
public:
	AdjMatrixGraph();
	~AdjMatrixGraph();
	bool adjacent(T, T);
	void addEdge(T, T);
	void deleteNode(T);
	void deleteEdge(T, T);
	void clearGraph();
	vector <T> neighbors(T);
	void dfs(AdjMatrixGraph<T>&, T, bool[]);
	void dfsHelper(AdjMatrixGraph<T>&, T);
	void bfs(AdjMatrixGraph<T>&, T, T);

private:
	T matrixAry[SIZE][SIZE];
};




//Using Vector for Adjacency List representation
template <class T>
class AdjListGraph {
public:
	AdjListGraph(); 
	~AdjListGraph();
	//bool adjacent(T, T);
	void addEdge(T, T);
	void deleteNode(T);
	void deleteEdge(T, T);
	//vector <T> neighbors(T);
	//void dfs(AdjListGraph<T>&, T, bool[]);
	//void dfsHelper(AdjListGraph<T>&, T);
	//void bfs(AdjListGraph<T>&, T, T);
	
private:
	vector<T> list[SIZE];
};




template<class T>
Graph<T>::Graph()
{

}

template<class T>
Graph<T>::~Graph()
{

}






// -------  Begin Adjacency Matrix  ----------


template<class T>
AdjMatrixGraph<T>::AdjMatrixGraph()
{
	clearGraph();

}




template<class T>
AdjMatrixGraph<T>::~AdjMatrixGraph()
{

}







template<class T>
bool AdjMatrixGraph<T>::adjacent(T x, T y)
{
	if (x >= SIZE || x < 0) {
		cout << "No vertice: " << x << endl << endl;
		return false;
	}
	if (y >= SIZE || y < 0) {
		cout << "No vertice: " << y << endl << endl;
		return false;
	}
	if (matrixAry[x][y] == NULL) {
		return false;
	}
	else {
		return true;
	}
}




template<class T>
void AdjMatrixGraph<T>::addEdge(T x, T y)
{
	if (x >= SIZE || x < 0) {
		cout << "No vertice: " << x << endl << endl;
		return;
	}
	if (y >= SIZE || y < 0) {
		cout << "No vertice: " << y << endl << endl;
		return;
	}
	if (matrixAry[x][y] == NULL) {
		matrixAry[x][y] = 1;
	}
}





template <class type>
void AdjMatrixGraph<type>::clearGraph() {

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			matrixAry[i][j] = NULL;
		}
	}

}






template<class T>
vector<T> AdjMatrixGraph<T>::neighbors(T x)
{
	vector <T> vector;

	for (int i = 0; i < 1; ++i) {  //only loop one time
		for (int j = 1; j < SIZE; ++j) {
			if (matrixAry[x][j] != NULL) {
				vector.push_back(j);
			}
		}
	}
	return vector;
}





// cite:  https://www.youtube.com/watch?v=Y40bRyPQQr0
// Used this video to help understand how to implement 
// graph depth-first search recursively

//cite: http://www.drdobbs.com/cpp/lambdas-in-c11/240168241
// Used to help understand lambdas

template<class T>
void AdjMatrixGraph<T>::dfs(AdjMatrixGraph<T>& g, T v, bool visited[])
{
	vector<T> vector;
	typename vector<T>::iterator it;
	visited[v] = true;

	auto func = [](T v) { visit(v); };  //lambda, call visit method
	func(v);

	vector = g.neighbors(v);

	for (it = vector.begin(); it != vector.end(); ++it) {
		if (!visited[*it]) {   //if element is false, it has not been visited
			dfs(g, *it, visited);
		}
	}
}






// cite:  https://www.youtube.com/watch?v=Y40bRyPQQr0
// Used this video to help understand how to implement 
// graph depth-first search recursively
template<class T>
void AdjMatrixGraph<T>::dfsHelper(AdjMatrixGraph <T> &graph, T v)
{
	bool *p = new bool[SIZE];
	for (int i = 1; i < SIZE; ++i) {
		p[i] = false;
	}

	graph.dfs(graph, v, p);
}





template<class T>
void AdjMatrixGraph<T>::bfs(AdjMatrixGraph<T>& graph, T v, T start)
{
	bool *p = new bool[SIZE];
	queue <T> queue;
	vector <T> connections;
	typename vector<T>::iterator it;

	if (start >= SIZE) {
		"Invalid size";
	}
	for (int i = 1; i < SIZE; ++i) {
		p[i] = false;
	}

	p[start] = true;
	queue.push(start);

	while (!queue.empty()) {
		connections = graph.neighbors(queue.front());
		cout << queue.front() << " ";
		auto func = [](T v) { visit(v); };    //lambda function, call "visit" method
		func(v);
		queue.pop();

		for (it = connections.begin(); it != connections.end(); ++it) {
			if (!p[*it]) {
				p[*it] = true;
				queue.push(*it);
			}
		}
	}
}




template<class T>
void AdjMatrixGraph<T>::deleteNode(T x) {

	// before deleting node "x", take care of
	// all nodes with edges to the node
	// that is about to be deleted

	for (int i = 0; i < SIZE; ++i) {
		if (matrixAry[i][x] == 1) {
			matrixAry[i][x] = NULL;
		}
	}

	//delete node
	int j = 0;
	for (; j < SIZE; ++j) {
		matrixAry[x][j] = NULL;
	}

}






template<class T>
void AdjMatrixGraph<T>::deleteEdge(T x, T y) {

	// validating the edge is within the array 

	if (x >= SIZE || x < 0) {
		cout << "No vertice: " << x << endl << endl;
		return;
	}
	if (y >= SIZE || y < 0) {
		cout << "No vertice: " << y << endl << endl;
		return;
	}

	matrixAry[x][y] = NULL;  //delete edge
}




template<class T>
void printVector(vector <T> vector)
{
	auto it = vector.begin();

	for (; it != vector.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n";
}




// This method is executed via lambda
// inside the dfs/bfs methods above.

template <class T>
void visit(T node)
{
	if (node >= SIZE || node < 0) {
		return;
	}

	cout << node << " ";
}






// -------  Begin Adjacency List  ----------
template<class T>
AdjListGraph<T>::AdjListGraph()
{

}

template<class T>
AdjListGraph<T>::~AdjListGraph()
{

}





// cite: https://www.geeksforgeeks.org/range-based-loop-c/
//for understanding range-based for loops

template<class T>
void AdjListGraph<T>::addEdge(T vertice, T edge)
{	
	
	//check if already exists
	for (int i = 0; i < 1; ++i) {
		for (T e : list[vertice]) {
			if (e == edge) {
				cout << "Edge already exists, not adding edge!\n";
				return;
			}
		}
	}
	
	if (vertice >= SIZE || vertice < 0) {
		cout << "Invalid vertice: " << vertice << endl << endl;
		return;
	}
	if (edge >= SIZE || edge < 0) {
		cout << "Invalid edge: " << edge << endl << endl;
		return;
	}

	list[vertice].push_back(edge);
}






template<class T>
void AdjListGraph<T>::deleteNode(T vertice)
{
	if (vertice >= SIZE || vertice < 0) {
		cout << "Invalid vertice: " << vertice << endl << endl;
		return;
	}

	list[vertice].clear();

}




template<class T>
void AdjListGraph<T>::deleteEdge(T vertice, T edge)
{
	if (vertice >= SIZE || vertice < 0) {
		cout << "Invalid vertice: " << vertice << endl << endl;
		return;
	}
	if (edge >= SIZE || edge < 0) {
		cout << "Invalid edge: " << edge << endl << endl;
		return;
	}


	for (auto it = list[vertice].begin(); it != list[vertice].end(); ++it) {
		if (*it == edge) {
			list[vertice].erase(it);
			break;  //we're done
		}
	}


}



int main()
{
	AdjMatrixGraph <int> graph;
	AdjListGraph<int>listGraph;

	listGraph.addEdge(1, 5);
	listGraph.addEdge(5, 3);
	listGraph.deleteNode(5);


	//graph.dfsHelper(graph, 1);
	//cout << "\n\n";
	//graph.bfs(graph, 1, 1);


	/* BEFORE ENDING THIS PROGRAM, MAKE
	   SURE TO INHERIT GRAPH CLASS TO
	   ADJLISTGRAPH AFTER ALL METHODS HAVE
	   BEEN CREATED ANDN TESTED*/

    return 0;
}



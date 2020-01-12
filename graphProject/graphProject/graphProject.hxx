#include "graphProject.h"
#pragma once


template <class T>
bool AdjacencyMatrixGraph<T>::adjacent(T x, T y) 
{
	if (this->adjMatrixArray[x][y] == NULL) {
		return false;
	}
	else {
		return true;  // adjacency exists
	}
}




// cite:  http://www.cplusplus.com/reference/random/
// Used this link to understand how the <random> library works.
//cite: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
// Used to understand how to efficiently use double pointers to create a matrix.
template<class T>
int ** AdjacencyMatrixGraph<T>::generateNewGraph(int numOfNodes, double edgeProbability) 
{
	default_random_engine generator;
	uniform_int_distribution<int> distro(0, numOfNodes - 1);
	int randomEdgeCounter = distro(generator);
	this->size = numOfNodes;
	this->adjMatrixArray = new int*[numOfNodes]; // adjacency matrix table

												 //creating graph matrix
	for (int i = 0; i < this->size; ++i) {
		this->adjMatrixArray[i] = new int[numOfNodes];
	}

	//initialize all nodes to null edges
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < size; ++j) {
			this->adjMatrixArray[i][j] = false;
		}
	}


	//adding edges to nodes randomly
	for (int i = 0; i < this->size; ++i) {
		randomEdgeCounter = distro(generator);  // get random index to begin adding edges to Ith vertex
		for (int j = randomEdgeCounter; j < this->size; ++j) {
			this->adjMatrixArray[i][j] = true;
			j = distro(generator); // randomize edge
		}
	}
	return this->adjMatrixArray;
}





template <class T>
void AdjacencyMatrixGraph<T>::displayMatrixGraph() 
{
	for (int i = 0; i < this->size; ++i) {
		cout << i << " --> ";
		for (int j = 0; j < this->size; ++j) {
			cout << adjMatrixArray[i][j] << " ";
		}
		cout << endl;
	}
}





template<class T>
vector<int> AdjacencyMatrixGraph<T>::neighbors(T x)
{
	vector <int> myVect;

	for (int i = 0; i < this->size; ++i) {
		myVect.push_back(this->adjMatrixArray[x][i]);
	}
	return myVect;
}







template<class T>
void AdjacencyMatrixGraph<T>::addEdge(T x, T y)
{
	assert(x < this->size && x >=0);
	assert(y < this->size && y >= 0);
	if (this->adjMatrixArray[x][y] == NULL) {
		this->adjMatrixArray[x][y] = 1;  //add edge
	}
}




template<class T>
void AdjacencyMatrixGraph<T>::deleteEdge(T x, T y)
{
	assert(x < this->size && x >= 0);
	assert(y < this->size && y >= 0);
	if (this->adjMatrixArray[x][y] == 1) {
		this->adjMatrixArray[x][y] = NULL;  //add edge
	}
}


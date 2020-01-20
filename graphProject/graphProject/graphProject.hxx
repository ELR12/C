#include "graphProject.h"
#pragma once


template <class T>
Graph<T>::Graph()
{


}


template <class T>
Graph<T>::~Graph()
{


}




template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph()
{
	this->size = 0;
}






template <class T>
AdjacencyListGraph<T>::~AdjacencyListGraph()
{


}




template <class T>
AdjacencyListGraph<T>&  AdjacencyListGraph<T>::generateNewGraph(int numOfNodes, double edgeProbability)
{
	AdjacencyListGraph graph;
	default_random_engine generator;
	uniform_int_distribution<int> distro(0, numOfNodes - 1);
	int randomEdgeCounter = distro(generator);
	this->size = numOfNodes;
	int save;


	//create vertexes
	for (int i = 0; i < this->size; ++i) {
		this->myList[i].push_back(i);
	}


	//adding edges to nodes randomly
	for (int i = 0; i < this->size; ++i) {
		randomEdgeCounter = distro(generator);  // randomize vertex numbers
		for (int j = randomEdgeCounter; j < this->size; ++j) {
			j = distro(generator); // randomize edge
			this->myList[i].push_back(randomEdgeCounter);
			randomEdgeCounter = distro(generator);  // randomize vertex numbers
		}
	}


	//sorts all vertexes so that unique function will remove any duplicate edges
	for (int i = 0; i < this->size; ++i) {
		save = this->myList[i].front();
		this->myList[i].sort();
		this->myList[i].unique();
		this->myList[i].push_front(save);  //vertex number
	}
	return graph;
}




template <class T>
void AdjacencyListGraph<T>::displayListGraph()
{

	for (int i = 0; i < this->size; ++i) {
		for (this->listIter = this->myList[i].begin(); this->listIter != this->myList[i].end(); ++this->listIter) {
			cout << *this->listIter << " ";
		}
		cout << endl;
	}
}






template <class T>
bool AdjacencyListGraph<T>::adjacent(T x, T y)
{
	bool found = false;
	for (this->listIter = this->myList[x].begin(); this->listIter != this->myList[x].end(); ++this->listIter) {
		if (*this->listIter == y) {
			found = true;
			break;
		}
	}
	return found;
}








template<class T>
vector<int> AdjacencyListGraph<T>::neighbors(T x)
{
	vector <int> myVect;
	assert(x < this->size && x >= 0);


	for (this->listIter = this->myList[x].begin(); this->listIter != this->myList[x].end(); ++this->listIter) {
		myVect.push_back(*this->listIter);
	}
	return myVect;
}








template<class T>
void AdjacencyListGraph<T>::addEdge(T x, T y)
{
	bool found = false;
	assert(x < this->size && x >= 0);
	assert(y < this->size && y >= 0);

	for (this->listIter = this->myList[x].begin(); this->listIter != this->myList[x].end(); ++this->listIter) {
		if (*this->listIter == y) {
			found = true;
			break;
		}
	}
	if (found == false) {  // if edge "y" does not exit, add edge "y"
		this->myList[x].push_back(y);
	}
}






template<class T>
void AdjacencyListGraph<T>::deleteEdge(T x, T y)
{
	assert(x < this->size && x >= 0);
	assert(y < this->size && y >= 0);
	this->myList[x].remove(y);  // remove the edge from x to y
}




template<class T>
void AdjacencyListGraph<T>::deleteNode(T x)
{
	assert(x < this->size && x >= 0);
	for (int i = 0; i < this->size; ++i) {
		this->myList[i].remove(x);
	}
}


template<class T>
void AdjacencyListGraph<T>::visit(T node)
{
	cout << "I am inside the 'visit' lambda function and am processing vertex: " << node << endl;;
}








// This function implements a lambda function that
// points to the "visit" function
// cite:  https://en.cppreference.com/w/cpp/language/lambda
// cite: 'Data Structures and Other Objects Using C++ by Main/Savitch'

template<class T>
void AdjacencyListGraph<T>::bfs(AdjacencyListGraph &g, T &startNode)
{
	vector <bool> processedVect;
	vector <T> connections;
	vector <int>::iterator itr;
	queue <T> vertexQueue;
	T processingNode = startNode;
	auto lambdaVisit = [&]() {this->visit(processingNode); };  // lambda expression for "visit" function

	assert(startNode < g.size && startNode >= 0);
	for (int i = 0; i < this->size; ++i) {  //init array
		processedVect.push_back(false);
	}

	processedVect[startNode] = true;
	vertexQueue.push(startNode);
	while (!vertexQueue.empty()) {
		connections = g.neighbors(vertexQueue.front());
		auto lambdaVisit = [&]() {this->visit(vertexQueue.front()); };
		lambdaVisit();
		vertexQueue.pop();
		for (itr = connections.begin(); itr != connections.end(); ++itr) {
			if (processedVect[*itr] == false) {
				processedVect[*itr] = true;
				vertexQueue.push(*itr);  //push vertex number into queue
			}
		}
	}
}




template<class T>
void AdjacencyListGraph<T>::dfsHelper(AdjacencyListGraph& g, T startNode, vector<bool> &processedVect, int index)
{
	vector <T> connections = g.neighbors(startNode);
	vector <int>::iterator iter;
	processedVect[startNode] = true;
	index = startNode;
	auto lambdaVisit = [&]() {this->visit(startNode); };
	lambdaVisit();

	for (iter = connections.begin(); iter != connections.end(); ++iter) {
		if (!processedVect[*iter]) {
			dfsHelper(g, *iter, processedVect, index);
		}
	}
}




template<class T>
void AdjacencyListGraph<T>::dfs(AdjacencyListGraph& g, T &startNode)
{
	vector <bool> processedVect;
	int index = 0;

	assert(startNode < g.size && startNode >= 0);
	for (int i = 0; i < this->size; ++i) {  //init array
		processedVect.push_back(false);
	}
	g.dfsHelper(g, startNode, processedVect, index);

}
















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




template <class T>
AdjacencyMatrixGraph<T>::AdjacencyMatrixGraph()
{
	this->size = 0;

}




template <class T>
AdjacencyMatrixGraph<T>::~AdjacencyMatrixGraph()
{


}






// cite:  http://www.cplusplus.com/reference/random/
// Used this link to understand how the <random> library works.
//cite: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
// Used to understand how to efficiently use double pointers to create a matrix.
template<class T>
AdjacencyMatrixGraph<T>& AdjacencyMatrixGraph<T>::generateNewGraph(int numOfNodes, double edgeProbability)
{
	default_random_engine generator;
	uniform_int_distribution<int> distro(0, numOfNodes - 1);
	int randomEdgeCounter = distro(generator);
	this->size = numOfNodes;
	this->adjMatrixArray = new int*[numOfNodes]; // adjacency matrix table
	AdjacencyMatrixGraph graph;

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
	return graph;
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
	assert(x < this->size && x >= 0);
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




template<class T>
void AdjacencyMatrixGraph<T>::deleteNode(T x) 
{
	assert(x < this->size && x >= 0);


	// before deleting node "x", take care of
	// all nodes with edges to the node "x"
	for (int i = 0; i < this->size; ++i) {
		if (this->adjMatrixArray[i][x] == 1) {
			this->adjMatrixArray[i][x] = NULL;
		}
	}

	//delete all edges of node x
	for (int j = 0; j < this->size; ++j) {
		this->adjMatrixArray[x][j] = NULL;
	}
}









// This function implements a lambda function that
// points to the "visit" function
// cite:  https://en.cppreference.com/w/cpp/language/lambda
// cite: 'Data Structures and Other Objects Using C++ by Main/Savitch'

template<class T>
void AdjacencyMatrixGraph<T>::bfs(AdjacencyMatrixGraph &g, T &startNode)
{
	vector <bool> processedVect;
	vector <T> connections;
	queue <T> vertexQueue;
	T processingNode = startNode;
	auto lambdaVisit = [&]() {this->visit(processingNode); };  // lambda expression for "visit" function

	assert(startNode < g.size && startNode >= 0);
	for (int i = 0; i < this->size; ++i) {  //init array
		processedVect.push_back(false);
	}

	processedVect[startNode] = true;

	vertexQueue.push(startNode);
	while (!vertexQueue.empty()) {
		connections = g.neighbors(vertexQueue.front());

		auto lambdaVisit = [&]() {this->visit(vertexQueue.front()); };
		lambdaVisit();

		vertexQueue.pop();
		getVertexNumber(connections, processedVect, vertexQueue);

	}
}




//Helper function for bfs
template<class T>
void AdjacencyMatrixGraph<T>::getVertexNumber(vector<T> &connections, vector<bool> &processedVect, queue<T> &queue)
{
	int index = 0;
	vector<int>::iterator it;

	for (it = connections.begin(); it != connections.end(); ++it) {
		if (processedVect[index] == false) {
			processedVect[index] = true;
			queue.push(index);  //push vertex number into queue
		}
		++index;
	}
}





template<class T>
void AdjacencyMatrixGraph<T>::dfsHelper(AdjacencyMatrixGraph& g, T startNode, vector<bool> &processedVect, int index)
{
	vector <T> connections = g.neighbors(startNode);
	processedVect[startNode] = true;
	index = startNode;
	auto lambdaVisit = [&]() {this->visit(startNode); };
	lambdaVisit();

	for (int i = 0; i < g.size; ++i) {
		index = i;
		if (!processedVect[index]) {
			dfsHelper(g, index, processedVect, index);
		}
	}
}




template<class T>
void AdjacencyMatrixGraph<T>::dfs(AdjacencyMatrixGraph& g, T &startNode)
{
	vector <bool> processedVect;
	int index = 0;

	assert(startNode < g.size && startNode >= 0);
	for (int i = 0; i < this->size; ++i) {  //init array
		processedVect.push_back(false);
	}
	g.dfsHelper(g, startNode, processedVect, index);

}




template<class T>
void AdjacencyMatrixGraph<T>::visit(T node)
{
	cout << "I am inside the 'visit' lambda function and am processing vertex: " << node << endl;;
}









#include "Graph.h"

template<typename T>
Graph<T>::Graph(int reserveSize) {
	this->nodes.reserve(reserveSize);
	this->edges.reserve(reserveSize);
}
template<typename T>
Graph<T>::Graph(std::vector<Node<T>*>& nodes, std::vector<Edge<T>*>& edges) {
	this->nodes = nodes;
	this->edges = edges;
}

template<typename T>
void Graph<T>::addNode(Node<T>* node) {
	if (node) {
		nodes.push_back(node);
	} else {
		// TODO: error handling
	}
}

template<typename T>
void Graph<T>::addNode(std::string label, T data, bool marked, std::vector<Node<T>*>& adjacencyList) {
	Node<T>* newNode = new Node<T>(label, data, marked);
	addNode(newNode);
	if (!adjacencyList.empty()) {
		for (auto nodeIt = adjacencyList.begin(); node != adjacencyList.end(); node++) {
			newNode->linkTo(*nodeIt);
		}
	} 
}

template<typename T>
void Graph<T>::linkNodes(Node<T>* node1, Node<T>* node2)
{

}

template<typename T>
void Graph<T>::linkNodes(std::string node1, std::string node2)
{

}

template<typename T>
void Graph<T>::unlinkNodes(Node<T>* node1, Node<T>* node2)
{

}

template<typename T>
void Graph<T>::unlinkNodes(std::string node1, std::string node2)
{

}

template<typename T>
void Graph<T>::deleteNode(std::string node)
{

}

template<typename T>
void Graph<T>::deleteNode(Node<T>* node)
{

}

template<typename T>
Node<T>* Graph<T>::getNode(std::string node)
{

}

template<typename T>
void Graph<T>::freeAll()
{

}

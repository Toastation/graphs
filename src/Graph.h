#pragma once

#include <iostream>
#include <string>
#include <vector>

#define RESERVE_SIZE_DEFAULT 20

template<typename T>
class Edge;

template<typename T>
class Node {
private:
	std::string label;
	T data;
	bool marked;
	int posX, posY;
	std::vector<Edge<T>*> adjacencyList;
public:
	Node(std::string label, T data, bool marked = false, int posX = 0, int posY = 0, std::vector<Node*> = {}) {
		this->label = label;
		this->data = data;
		this->marked = marked;
		this->posX = posX;
		this->posY = posY;
		this->adjacencyList = adjacencyList;
	}

	/*
	 * @brief adds a new edge to the node
	 * @param the new edge
	 */
	void addEdge(Edge<T>* edge) {
		if (edge) {
			adjacencyList.push_back(edge);
		} else {
			// TODO: error handling
		}
	}

	/*
	 * @brief how many nodes is this node connected to
	 * @return the size of the adjacency list
	 */
	int getNumberOfNeighbors() {
		return adjacencyList.size();
	}

	/*
	* @brief the node's label
	* @return the node's label
	*/
	std::string& getLabel() {
		return label;
	}

	/*
	 * @brief the node's value
	 * @return the node's value
	 */
	T getData() {
		return data;
	}

	/*
	* @brief is the node marked
	* @return true if the node is marked
	*/
	bool isMarked() {
		return marked;
	}
};

template<typename T>
class Edge {
private:
	T data;
	bool marked;
	Node<T>* start;
	Node<T>* end;
public:
	Edge(Node<T>* start, Node<T>* end, T data = 0, bool marked = false) {
		this->start = start;
		this->end = end;
		this->data = data;
		this->marked = marked;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	Node<T>* getStart() {
		return start;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	Node<T> getEnd() {
		return end;
	}

	/*
	* @brief the edge's value
	* @return the node's value
	*/
	T getData() {
		return data;
	}

	/*
	* @brief is the edge marked
	* @return true if the edge is marked
	*/
	bool isMarked() {
		return marked;
	}
};

template<typename T>
class Graph {
private:
	std::vector<Node<T>*> nodes;
	std::vector<Edge<T>*> edges;
public:
	Graph(int reserveSize = RESERVE_SIZE_DEFAULT) {
		this->nodes.reserve(reserveSize);
		this->edges.reserve(reserveSize);
	}

	Graph(std::vector<Node<T>*>& nodes, std::vector<Edge<T>*>& edges) {
		this->nodes = nodes;
		this->edges = edges;
	}

	void addNode(Node<T>* node) {
		if (node) {
			nodes.push_back(node);
		}
		else {
			// TODO: error handling
		}
	}

	void addNode(std::string label, T data, bool marked = false, std::vector<Node<T>*> adjacencyList = {}) {
		Node<T>* newNode = new Node<T>(label, data, marked);
		addNode(newNode);
		if (!adjacencyList.empty()) {
			for (auto nodeIt = adjacencyList.begin(); nodeIt != adjacencyList.end(); nodeIt++) {
				linkNodes(newNode, *nodeIt);
				// TODO add unrecognized nodes to the vector
			}
		}
	}
	
	void linkNodes(std::string node1, std::string node2);
	void linkNodes(Node<T>* node1, Node<T>* node2) {
		Edge<T>* newEdge = new Edge<T>(node1, node2);
		if (node1 && node2 && newEdge) {
			edges.push_back(newEdge);
			node1->addEdge(newEdge);
			node2->addEdge(newEdge);
		} else {
			// TODO: error handling
		}
	}
	void unlinkNodes(std::string node1, std::string node2);
	void unlinkNodes(Node<T>* node1, Node<T>* node2);
	void deleteNode(Node<T>* node);
	void deleteNode(std::string node);

	void printNodes() {
		std::cout << "[ ";
		for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
			Node<T>* node = *nodeIt;
			std::cout << node->getLabel() << " ";
		}
		std::cout << "]" << std::endl;
	}

	Node<T>* getNode(std::string node);
	void freeAll();
};
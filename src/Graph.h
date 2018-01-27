#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

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
	std::vector<const Edge<T>*> adjacencyList;
public:
	Node(std::string label, T data, bool marked = false, int posX = 0, int posY = 0) {
		this->label = label;
		this->data = data;
		this->marked = marked;
		this->posX = posX;
		this->posY = posY;
		this->adjacencyList = {};
	}

	/*
	 * @brief adds a new edge to the node's adjacency list. Stores a const raw pointer equivalent of the unique pointer
	 * @param edge a reference to the unique pointer of the new edge
	 */
	void addEdge(const std::unique_ptr<Edge<T>>& edge) {
		adjacencyList.push_back(edge.get());
	}

	/*
	 * @brief returns the number of edges connected to this node
	 * @return the size of the adjacency list
	 */
	int getNumberOfEdges() {
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
	std::string label;
	T data;
	bool marked;
	const Node<T>* start;
	const Node<T>* end;
public:
	Edge(std::string label, const std::unique_ptr<Node<T>>& start, const std::unique_ptr<Node<T>>& end, T data = 0, bool marked = false) {
		this->label = label;
		this->start = start.get();
		this->end = end.get();
		this->data = data;
		this->marked = marked;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	const Node<T>* getStart() {
		return start;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	const Node<T> getEnd() {
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
	std::unordered_map<std::string, std::unique_ptr<Node<T>>> nodes;
	std::unordered_map<std::string, std::unique_ptr<Edge<T>>> edges;
public:
	Graph(int reserveSize = RESERVE_SIZE_DEFAULT) {
		this->nodes.reserve(reserveSize);
		this->edges.reserve(reserveSize);
	}

	/*
	 * @brief allocates a new node, stores it into a unique pointer and adds it to the graph
	 * @param label label of the node
	 * @param data data of the node
	 * @param marked is the node marked 
	 */
	void addNode(std::string label, T data, bool marked = false) {
		nodes.insert(std::make_pair(label, std::make_unique<Node<T>>(label, data, marked)));
	}
	
	/*
	 * @brief allocates a new edge, stores it into a unique pointer and adds it to the graph
	 * @param label label of the edge 
	 * @param node1 starting node of the edge
	 * @param node2 ending node of the edge 
	 */
	void linkNodes(std::string label, const std::unique_ptr<Node<T>>& node1, const std::unique_ptr<Node<T>>& node2) {
		if (node1 && node2) {
			edges.insert(std::make_pair(label, std::make_unique<Edge<T>>(label, node1, node2)));
			const std::unique_ptr<Edge<T>>& newEdge = edges[label];
			node1->addEdge(newEdge);
			node2->addEdge(newEdge);
		} else {
			// TODO: error handling
		}
	}

	/*
	* @brief allocates a new edge, stores it into a unique pointer and adds it to the graph
	* @param label label of the edge
	* @param node1 starting node of the edge
	* @param node2 ending node of the edge
	*/
	void linkNodes(std::string label, std::string node1, std::string node2) {
		linkNodes(label, nodes[node1], nodes[node1]);
	}
	
	void unlinkNodes(std::string node1, std::string node2);
	void unlinkNodes(Node<T>* node1, Node<T>* node2);
	void deleteNode(Node<T>* node);
	void deleteNode(std::string node);

	void printNodes() {
		std::cout << "[ ";
		for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
			std::cout << nodeIt->first << ", ";
		}
		std::cout << "]" << std::endl;
	}
};
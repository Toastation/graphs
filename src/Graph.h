#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#define RESERVE_SIZE_DEFAULT 20
#define MAX_DISTANCE_SQUARED 100

template<typename T>
class Edge;

template<typename T>
class Node {
private:
	std::string label;
	T data;
	bool selected;
	bool marked;
	float posX;
	float posY;
	float netForceX;
	float netForceY;
	std::vector<const Edge<T>*> adjacencyList;
public:
	Node(std::string label, T data, bool marked = false, float posX = 0.0f, float posY = 0.0f) {
		this->label = label;
		this->data = data;
		this->selected = false;
		this->marked = marked;
		this->posX = posX;
		this->posY = posY;
		this->netForceX = 0.0f;
		this->netForceY = 0.0f;
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
	 * @brief deletes an edge connected to this node
	 * @param edge the label of the edge
	 */
	void deleteEdge(std::string edge) {
		auto it = adjacencyList.begin();
		while (it != adjacencyList.end()) {
			const Edge<T>* e = *it;
			if (e->getLabel() == edge) {
				it = adjacencyList.erase(it);
			}
			else {
				it++;
			}
		}
	}

	/*
	 * @brief translates the node's position 
	 */
	void translate(float dx, float dy) {
		posX += dx;
		posY += dy;
	}

	/*
	 * @brief applies given changes to the node's net force 
	 */
	void applyForce(float fx, float fy) {
		netForceX += fx;
		netForceY += fy;
	}

	/*
	 * @brief the degree of nodes
	 * @return the size of the adjacency list
	 */
	int degree() const {
		return adjacencyList.size();
	}

	/*
	 * @brief returns a list of the nodes that are n edges apart (0 being the current node)
	 * @param n the number of edges between the current node and the wanted nodes
	 * @return a list of the nodes that are n edges apart
	 */
	std::vector<std::string> getNDistanceNeighbors(int n) {
		if (n < 0) {
			std::cerr << "In getNDistanceNeighbors(int n): n should > 0." << std::endl;
			return nullptr;
		}
		else if (n == 0) {
			std::vector<std::string> labelList;
			for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
				labelList.push_back((*it)->getLabel());
			}
			return labelList;
		}
		std::vector<std::string> finalLabelList;
		std::vector<std::string> neighborList = getNDistanceNeighbors(n - 1);
		finalLabelList.insert(finalLabelList.end(), neighborList.begin(), neighborList.end());
		return finalLabelList;
	}

	/*
	* @brief the node's label
	* @return the node's label
	*/
	std::string getLabel() const {
		return label;
	}

	/*
	 * @brief the node's value
	 * @return the node's value
	 */
	T getData() const {
		return data;
	}

	/*
	 * @brief the node's x coordinate
	 * @return the node's x coordinate
	 */
	float getPosX() const {
		return posX;
	}

	/*
	* @brief the node's y coordinate
	* @return the node's y coordinate
	*/
	float getPosY() const {
		return posY;
	}

	/*
	 * @brief the node's net force x component
	 * @return the node's net force x component
	 */
	float getNetForceX() const {
		return netForceX;
	}

	/*
	 * @brief the node's net force y component
	 * @return the node's net force y component
	 */
	float getNetForceY() const {
		return netForceY;
	}

	/*
	 * @brief returns if the node is selected or not
	 * @return if the node is selected or not
	 */
	bool isSelected() const {
		return selected;
	}

	/*
	* @brief is the node marked
	* @return true if the node is marked
	*/
	bool isMarked() const {
		return marked;
	}

	/*
	 * @brief returns the adjacency list of the node
	 * @return the adjacency list of the node
	 */
	const std::vector<const Edge<T>*> getAdjacencyList() const {
		return adjacencyList;
	}

	/*
	 * @brief select or deselect the node
	 * @param whether or not the node should be selected
	 */
	void setSelected(bool selected) {
		this->selected = selected;
	}

	/*
	* @brief mark or unmark the node
	*/
	void setMarked(bool marked) {
		this->marked = marked;
	}

	/*
	 * @brief set the x coordinate of the node
	 * @param x the new coordinate of the node
	 */
	void setPosX(float x) {
		posX = x;
	}

	/*
	 * @brief set the y coordinate of the node
	 * @param y the new coordinate of the node
	 */
	void setPosY(float y) {
		posY = y;
	}

	/*
	* @brief set the y coordinate of the node
	* @param y the new coordinate of the node
	*/
	void setNetForce(float netForceX, float netForceY) {
		this->netForceX = netForceX;
		this->netForceY = netForceY;
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
	 * @brief mark or unmark the edge
	 */
	void setMarked(bool marked) {
		this->marked = marked;
	}

	/*
	* @brief the node's label
	* @return the node's label
	*/
	std::string getLabel() const {
		return label;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	const Node<T>* getStart() const {
		return start;
	}

	/*
	* @brief the edge's value
	* @return the edge's value
	*/
	const Node<T>* getEnd() const {
		return end;
	}

	/*
	* @brief the edge's value
	* @return the node's value
	*/
	T getData() const {
		return data;
	}

	/*
	* @brief is the edge marked
	* @return true if the edge is marked
	*/
	bool isMarked() const {
		return marked;
	}
};

typedef const std::unordered_map<std::string, std::unique_ptr<Node<int>>>& NodesRef_Int;
typedef const std::unordered_map<std::string, std::unique_ptr<Edge<int>>>& EdgesRef_Int;

template<typename T>
class Graph {
private:
	std::unordered_map<std::string, std::unique_ptr<Node<T>>> nodes;
	std::unordered_map<std::string, std::unique_ptr<Edge<T>>> edges;
	float springRestLength;
	float springFactor;
	float repulsiveFactor;
	float delta;
	float highestSquaredDistance;
	float ratio;
public:
	Graph(int reserveSize = RESERVE_SIZE_DEFAULT) {
		this->nodes.reserve(reserveSize);
		this->edges.reserve(reserveSize);
		this->springRestLength = 100.0f;
		this->springFactor = 1.0f;
		this->repulsiveFactor = 6250.0f;
		this->delta = 0.0004f;
		this->highestSquaredDistance = 0.0f;
		this->ratio = repulsiveFactor / std::pow(springRestLength, 3);
	}

	/*
	 * @brief allocates a new node, stores it into a unique pointer and adds it to the graph
	 * @param label label of the node
	 * @param data data of the node
	 * @param marked is the node marked 
	 * @param posX the x coordinate of the node
	 * @param posY the y coordinate of the node
	 */
	void addNode(std::string label, T data, bool marked = false, float posX = 0.0f, float posY = 0.0f) {
		nodes.insert(std::make_pair(label, std::make_unique<Node<T>>(label, data, marked, posX, posY)));
	}
	
	/*
	 * @brief allocates a new edge, stores it into a unique pointer and adds it to the graph
	 * @param label label of the edge 
	 * @param node1 starting node of the edge
	 * @param node2 ending node of the edge 
	 */
	void linkNodes(std::string label, const std::unique_ptr<Node<T>>& node1, const std::unique_ptr<Node<T>>& node2, bool marked = false) {
		if (node1 && node2) {
			edges.insert(std::make_pair(label, std::make_unique<Edge<T>>(label, node1, node2, 0, marked)));
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
	void linkNodes(std::string label, std::string node1, std::string node2, bool marked = false) {
		linkNodes(label, nodes[node1], nodes[node2], marked);
	}
	
	/*
	 * @brief deletes an edge between 2 nodes
	 * @param edge the edge to delete
	 */
	void unlinkNodes(std::string edge) {
		nodes[edges[edge]->getStart()->getLabel()]->deleteEdge(edge);
		nodes[edges[edge]->getEnd()->getLabel()]->deleteEdge(edge);
		edges.erase(edge);
	}

	/*
	* @brief translates the position of the given node
	* @param node the node to translate
	* @param dx the value of translation on the x-axis
	* @param dy the value of translation on the y-axis
	*/
	void translateNode(std::string node, float dx, float dy) {
		nodes[node]->translate(dx, dy);
	}

	/*
	 * @brief select or deselect the given node
	 * @param the node to select/deselect
	 */
	void selectNode(std::string node, bool selected) {
		nodes[node]->setSelected(selected);
	}

	/*
	 * @brief unselect all the nodes
	 */
	void unselectAll() {
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			selectNode((it->second)->getLabel(), false);
		}
	}

	/*
	* @brief mark or unmark an edge
	* @param edge the edge to be marked or unmarked
	* @param marked true if the edge is marked, false otherwise
	*/
	void markEdge(std::string edge, bool marked) {
		edges[edge]->setMarked(marked);
	}

	/*
	 * @brief mark or unmark a node
	 * @param node the node to be marked or unmarked
	 * @param marked true if the node is marked, false otherwise
	 */
	void markNode(std::string node, bool marked) {
		nodes[node]->setMarked(marked);
	}

	/*
	 * @brief mark or unmark a node and its adjacent edges
	 * @param node the node to be marked or unmarked
	 * @param marked true if the node is marked, false otherwise
	 */
	void markNodeAndEdges(std::string node, bool marked) {
		nodes[node]->setMarked(marked);
		const std::vector<const Edge<T>*> list = nodes[node]->getAdjacencyList();
		for (auto it = list.begin(); it != list.end(); it++) {
			const Edge<T>* edge = *it;
			markEdge(edge->getLabel(), marked);
		}
	}

	/*
	 * @brief mark or unmark all the adjacent edges of a node, but not the node itself
	 * @param node the node to be marked or unmarked
	 * @param marked true if the node is marked, false otherwise
	 */
	void markEdgesOfNode(std::string node, bool marked) {
		const std::vector<const Edge<T>*> list = nodes[node]->getAdjacencyList();
		for (auto it = list.begin(); it != list.end(); it++) {
			const Edge<T>* edge = *it;
			markEdge(edge->getLabel(), marked);
		}
	}

	/*
	 * @brief marl or unmark all nodes and edges of the graph
	 * @param marked true if the node is marked, false otherwise
	 */
	void markAll(bool marked) {
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			markNodeAndEdges((it->second)->getLabel(), marked);
		}
	}

	/*
	 * @brief deletes all nodes and edges
	 */
	void clearGraph() {
		nodes.clear();
		edges.clear();
	}

	/*
	 * @brief randomizes the position of the nodes
	 */
	void randomizePos(float x, float y, int width, int height) {
		std::srand((unsigned int)std::time(nullptr));
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			it->second->setPosX(x + (std::rand() % width) + 1);
			it->second->setPosY(y + (std::rand() % height) + 1);
		}
	}

	/*
	 * @brief applies a force-based algorithm on the node's layout
	 */
	void forceBasedLayout(float deltaFrame) {
		float dx = 0.0f;
		float dy = 0.0f;
		float fx = 0.0f;
		float fy = 0.0f;
		float distance = 0.0f;
		float distanceSquared = 0.0f;
		float repulsiveForceMagnitude = 0.0f;
		float springForceMagnitude = 0.0f;
		// compute repulsive forces
		for (auto it1 = nodes.begin(); it1 != (nodes.end()--); it1++) {
			std::unique_ptr<Node<T>>& node1 = it1->second;
			for (auto it2 = (nodes.begin()++); it2 != nodes.end(); it2++) {
				std::unique_ptr<Node<T>>& node2 = it2->second;
				dx = node2->getPosX() - node1->getPosX();
				dy = node2->getPosY() - node1->getPosY();
				if (dx != 0 || dy != 0) {
					distanceSquared = (dx * dx) + (dy * dy);
					distance = std::sqrt(distanceSquared);
					repulsiveForceMagnitude = repulsiveFactor / distanceSquared;
					fx = (repulsiveForceMagnitude * dx) / distance;
					fy = (repulsiveForceMagnitude * dy) / distance;
					node1->applyForce(-fx, -fy);
					node2->applyForce(fx, fy);
				}
			}
		}
		// compute spring forces
		for (auto it = edges.begin(); it != edges.end(); it++) {
			std::unique_ptr<Node<T>>& node1 = nodes[it->second->getStart()->getLabel()];
			std::unique_ptr<Node<T>>& node2 = nodes[it->second->getEnd()->getLabel()];
			dx = node2->getPosX() - node1->getPosX();
			dy = node2->getPosY() - node1->getPosY();
			distanceSquared = (dx * dx) + (dy * dy);
			distance = std::sqrt(distanceSquared);
			springForceMagnitude = springFactor * (distance - springRestLength);
			fx = (springForceMagnitude * dx) / distance;
			fy = (springForceMagnitude * dy) / distance;
			node1->applyForce(fx, fy);
			node2->applyForce(-fx, -fy);
		}
		// update positions
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			std::unique_ptr<Node<T>>& node = it->second;
			dx = delta * node->getNetForceX();
			dy = delta * node->getNetForceY();
			distanceSquared = (dx * dx) + (dy * dy);
			if (distanceSquared > highestSquaredDistance) {
				highestSquaredDistance = distanceSquared;
			}
			if (distanceSquared >= MAX_DISTANCE_SQUARED) {
				float s = std::sqrt(MAX_DISTANCE_SQUARED / distanceSquared);
				dx *= s;
				dy *= s;
			}
			//std::cout << "dsquared: " << ((dx*dx) + (dy*dy)) << std::endl;
			node->translate(dx*deltaFrame, dy*deltaFrame);
			node->setNetForce(0.0f, 0.0f);
		}
	}

	/*
	 * @brief applies a force-based algorithm on the node's layout
	 */
	void forceBasedLayout2(float deltaFrame) {
		float dx = 0.0f;
		float dy = 0.0f;
		float fx = 0.0f;
		float fy = 0.0f;
		float distance = 0.0f;
		float distanceSquared = 0.0f;
		float repulsiveForceMagnitude = 0.0f;
		float springForceMagnitude = 0.0f;
		// compute spring forces to D1 neighbors
		for (auto it = edges.begin(); it != edges.end(); it++) {
			std::unique_ptr<Node<T>>& node1 = nodes[it->second->getStart()->getLabel()];
			std::unique_ptr<Node<T>>& node2 = nodes[it->second->getEnd()->getLabel()];
			dx = node2->getPosX() - node1->getPosX();
			dy = node2->getPosY() - node1->getPosY();
			distanceSquared = (dx * dx) + (dy * dy);
			distance = std::sqrt(distanceSquared);
			springForceMagnitude = springFactor * (distance - springRestLength);
			fx = (springForceMagnitude * dx) / distance;
			fy = (springForceMagnitude * dy) / distance;
			node1->applyForce(fx, fy);
			node2->applyForce(-fx, -fy);
			// computing spring to D2 neighbors
			const std::vector<const Edge<T>*> node1Neighbors = node1->getAdjacencyList();
			const std::vector<const Edge<T>*> node2Neighbors = node2->getAdjacencyList();
			for (auto it2 = node1Neighbors.begin(); it2 != node1Neighbors.end(); it2++) {
				const Edge<T>* edge = *it2;
				std::string startLabel = edge->getStart()->getLabel();
				std::unique_ptr<Node<T>>& neighbor = (startLabel == node1->getLabel()) ? nodes[edge->getEnd()->getLabel()] : nodes[startLabel];
				if (neighbor->getLabel() != node2->getLabel()) {
					dx = node2->getPosX() - neighbor->getPosX();
					dy = node2->getPosY() - neighbor->getPosY();
					distanceSquared = (dx * dx) + (dy * dy);
					distance = std::sqrt(distanceSquared);
					springForceMagnitude = springFactor * (distance - (2*springRestLength));
					fx = (springForceMagnitude * dx) / distance;
					fy = (springForceMagnitude * dy) / distance;
					neighbor->applyForce(fx, fy);
					node2->applyForce(-fx, -fy);
				}
			}
			for (auto it3 = node2Neighbors.begin(); it3 != node2Neighbors.end(); it3++) {
				const Edge<T>* edge = *it3;
				std::string startLabel = edge->getStart()->getLabel();
				std::unique_ptr<Node<T>>& neighbor = (startLabel == node2->getLabel()) ? nodes[edge->getEnd()->getLabel()] : nodes[startLabel];
				if (neighbor->getLabel() != node1->getLabel()) {
					dx = neighbor->getPosX() - node1->getPosX();
					dy = neighbor->getPosY() - node1->getPosY();
					distanceSquared = (dx * dx) + (dy * dy);
					distance = std::sqrt(distanceSquared);
					springForceMagnitude = springFactor * (distance - (2 * springRestLength));
					fx = (springForceMagnitude * dx) / distance;
					fy = (springForceMagnitude * dy) / distance;
					node1->applyForce(fx, fy);
					neighbor->applyForce(-fx, -fy);
				}
			}
		}
		// update positions
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			std::unique_ptr<Node<T>>& node = it->second;
			dx = delta * node->getNetForceX();
			dy = delta * node->getNetForceY();
			distanceSquared = (dx * dx) + (dy * dy);
			if (distanceSquared > highestSquaredDistance) {
				highestSquaredDistance = distanceSquared;
			}
			if (distanceSquared >= MAX_DISTANCE_SQUARED) {
				float s = std::sqrt(MAX_DISTANCE_SQUARED / distanceSquared);
				dx *= s;
				dy *= s;
			}
			//std::cout << "dsquared: " << ((dx*dx) + (dy*dy)) << std::endl;
			node->translate(dx*deltaFrame, dy*deltaFrame);
			node->setNetForce(0.0f, 0.0f);
		}
	}

	/*
	 * @brief returns a const reference to the map of nodes
	 * @return a const reference to the map of nodes
	 */
	NodesRef_Int getNodes() const {
		return nodes;
	}

	/*
	 * @brief returns a const reference to the map of edges
	 * @return a const reference to the map of edges
	 */
	EdgesRef_Int getEdges() const {
		return edges;
	}

	/*
	 * @brief returns the speed factor of nodes translation
	 * @return the speed factor of nodes translation
	 */
	float getDelta() const {
		return delta;
	}

	/*
	 * @brief returns the spring factor of edges
	 * @return the spring factor of edges
	 */
	float getSpringFactor() const {
		return springFactor;
	}

	/*
	 * @brief returns the repulsive factor of nodes
	 * @return the spring repulsive of nodes
	 */
	float getRepulsiveFactor() const {
		return repulsiveFactor;
	}

	/*
	 * @brief returns the length of an edge at rest
	 * @return the length of an edge at rest
	 */
	float getSpringRestLength() const {
		return springRestLength;
	}

	// *** DEBUG ***
	float getHighestSquaredDistance() const {
		return highestSquaredDistance;
	}

	float getRatio() {
		return ratio;
	}
	
	void setHighestSquaredDistance(float v) {
		highestSquaredDistance = v;
	}

	void increaseRatio(float dx) {
		if (ratio - dx > 0) {
			ratio += dx;
		}
	}

	void setRatio(float newRatio) {
		ratio = newRatio;
	}
	// *** END DEBUG ***

	/*
	 * @brief prints all the nodes labels
	 */
	void printNodes() {
		std::cout << "[ ";
		for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
			std::cout << nodeIt->first << " ";
		}
		std::cout << "]" << std::endl;
	}
};
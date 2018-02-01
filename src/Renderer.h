#pragma once
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Graph.h"

class Renderer {
public:
	static void drawNode(sf::RenderWindow& window, float x, float y) {
		ResourceManager::nodeRect.setPosition(x, y);
		window.draw(ResourceManager::nodeRect);
	}

	static void drawEdge(sf::RenderWindow& window, sf::Vertex vertices[]) {
		window.draw(vertices, 2, sf::Lines);
	}
	
	static void drawGraph(sf::RenderWindow& window, const Graph<int>& graph) {
		NodesRef_Int nodes = graph.getNodes();
		EdgesRef_Int edges = graph.getEdges();
		for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
			drawNode(window, nodeIt->second->getPosX(), nodeIt->second->getPosY());
		}
		sf::Vertex vertices[] = {sf::Vector2f(), sf::Vector2f()};
		float xOffset = ResourceManager::nodeRect.getSize().x / 2;
		float yOffSet = ResourceManager::nodeRect.getSize().y / 2;
		for (auto edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++) {
			const Edge<int>* const edge = edgeIt->second.get();
			vertices[0].position.x = edge->getStart()->getPosX() + xOffset;
			vertices[0].position.y = edge->getStart()->getPosY() + yOffSet;
			vertices[1].position.x = edge->getEnd()->getPosX() + xOffset;
			vertices[1].position.y = edge->getEnd()->getPosY() + yOffSet;
			drawEdge(window, vertices);
		}
	}
private:
	Renderer();
};
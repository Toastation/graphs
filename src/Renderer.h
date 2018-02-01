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
	
	static void drawGraph(sf::RenderWindow& window, Graph<int>& graph) {
		NodesRef_Int nodes = graph.getNodes();
		for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
			drawNode(window, nodeIt->second->getPosX(), nodeIt->second->getPosY());
		}
	}
private:
	Renderer();
};
#pragma once
#include <ctime>
#include <cstring>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Graph.h"

class ResourceManager {
public:
	static std::unordered_map<std::string, std::unique_ptr<Graph<int>>> graphs;
	static std::unordered_map<std::string, sf::Font> fonts;
	static sf::RectangleShape nodeRect;

	static void generateRandomGraph(std::string graphName, int maxNodes, int maxEdges, int x, int y, int width, int height);
	static bool loadData();
private:
	ResourceManager();
};
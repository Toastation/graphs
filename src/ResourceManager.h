#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Graph.h"

class ResourceManager {
public:
	static std::unordered_map<std::string, Graph<int>> graphs;
	static std::unordered_map<std::string, sf::Font> fonts;
	static sf::RectangleShape nodeRect;

	static void loadData();
private:
	ResourceManager();
};
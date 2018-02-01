#include "ResourceManager.h"

std::unordered_map<std::string, Graph<int>> ResourceManager::graphs;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
sf::RectangleShape ResourceManager::nodeRect;

void ResourceManager::loadData() {
	Graph<int> g1;
	g1.addNode("n1", 5);
	//graphs.insert(std::make_pair<std::string, Graph<int>>("g1", g1));

	nodeRect.setPosition(0.0f, 0.0f);
	nodeRect.setSize(sf::Vector2f(20.0f, 20.0f));
	nodeRect.setFillColor(sf::Color::White);
}
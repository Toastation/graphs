#include "ResourceManager.h"

std::unordered_map<std::string, std::unique_ptr<Graph<int>>> ResourceManager::graphs;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
sf::RectangleShape ResourceManager::nodeRect;

void ResourceManager::loadData() {
	graphs["G1"] = std::make_unique<Graph<int>>();
	graphs["G1"]->addNode("N1", 5, false, 100.0f, -200.0f);
	graphs["G1"]->addNode("N2", 10, false, 100.0f, 100.0f);
	graphs["G1"]->linkNodes("E1", "N1", "N2");
	graphs["G1"]->unlinkNodes("E1");

	nodeRect.setPosition(0.0f, 0.0f);
	nodeRect.setSize(sf::Vector2f(10.0f, 10.0f));
	nodeRect.setFillColor(sf::Color::White);
}
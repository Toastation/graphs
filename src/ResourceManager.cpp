#include "ResourceManager.h"

std::unordered_map<std::string, std::unique_ptr<Graph<int>>> ResourceManager::graphs;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
sf::RectangleShape ResourceManager::nodeRect;

void ResourceManager::loadData() {
	graphs["G1"] = std::make_unique<Graph<int>>();
	graphs["G1"]->addNode("N1", 5, false, -200.0f, -200.0f);
	graphs["G1"]->addNode("N2", 10, false, 200.0f, -200.0f);
	graphs["G1"]->addNode("N3", 15, false, 200.0f, 200.0f);
	graphs["G1"]->addNode("N4", 20, false, -200.0f, 200.0f);
	graphs["G1"]->addNode("N5", 25, false, 0.0f, 0.0f);

	graphs["G1"]->linkNodes("E1", "N1", "N2");
	graphs["G1"]->linkNodes("E2", "N2", "N3");
	graphs["G1"]->linkNodes("E3", "N3", "N4");
	graphs["G1"]->linkNodes("E4", "N4", "N1");
	graphs["G1"]->linkNodes("E5", "N1", "N5");
	graphs["G1"]->linkNodes("E6", "N2", "N5");
	graphs["G1"]->linkNodes("E7", "N3", "N5");
	graphs["G1"]->linkNodes("E8", "N4", "N5");


	nodeRect.setPosition(0.0f, 0.0f);
	nodeRect.setSize(sf::Vector2f(10.0f, 10.0f));
	nodeRect.setFillColor(sf::Color::White);
}
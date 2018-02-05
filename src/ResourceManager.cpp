#include "ResourceManager.h"

std::unordered_map<std::string, std::unique_ptr<Graph<int>>> ResourceManager::graphs;
std::unordered_map<std::string, sf::Font> ResourceManager::fonts;
sf::RectangleShape ResourceManager::nodeRect;

void ResourceManager::generateRandomGraph(std::string graphName, int maxNodes, int maxEdges, int x, int y, int width, int height) {
	ResourceManager::graphs[graphName] = std::make_unique<Graph<int>>();
	std::srand((unsigned int)std::time(nullptr));
	int nbNodes = 2 + std::rand() % (maxNodes - 2);
	int nbEdges = std::rand() % maxEdges;
	std::cout << "Number of nodes: " << nbNodes << std::endl;
	std::cout << "Number of edges: " << nbEdges << std::endl;
	for (int i = 0; i < nbNodes; i++) {
		std::string nodeLabel = "N" + std::to_string(i);
		float nodeX = (float)(x + std::rand() % width);
		float nodeY = (float)(y + std::rand() % height);
		ResourceManager::graphs[graphName]->addNode(nodeLabel, 0, false, nodeX, nodeY);
	}
	for (int i = 0; i < nbEdges; i++) {
		std::string edgeLabel = "E" + std::to_string(i);
		int startNodeIndex = std::rand() % (nbNodes);
		int endNodeIndex = std::rand() % (nbNodes);
		while (endNodeIndex == startNodeIndex) {
			endNodeIndex = std::rand() % (nbNodes);
		}
		std::string startNodeLabel = "N" + std::to_string(startNodeIndex);
		std::string endNodeLabel = "N" + std::to_string(endNodeIndex);
		ResourceManager::graphs[graphName]->linkNodes(edgeLabel, startNodeLabel, endNodeLabel);
	}
}

bool ResourceManager::loadData() {
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

	generateRandomGraph("G2", 50, 20, -400, -300, 800, 600);

	if (!(fonts["infoFont"].loadFromFile("res/fonts/arial.ttf"))) {
		std::cout << "Failed to load res/fonts/arial.ttf" << std::endl;
		return false;
	}

	nodeRect.setPosition(0.0f, 0.0f);
	nodeRect.setSize(sf::Vector2f(10.0f, 10.0f));
	nodeRect.setFillColor(sf::Color::White);
	return true;
}
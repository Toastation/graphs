#include "Application.h"

Application::Application() {
	
}

Application::~Application() {

}

bool Application::init() {
	if (!ResourceManager::loadData()) {
		std::cout << "Failed to load data" << std::endl;
		return false;
	}
	initConstant();
	window.create(sf::VideoMode(800, 600), "Graph");
	//window.setFramerateLimit(60);
	defaultView.setSize(800, 600);
	defaultView.setCenter(400, 300);
	currentGraph = "G1";
	cam.init(0.0f, 0.0f, 800.0f, 600.0f);
	currentMousePos = sf::Mouse::getPosition(window);
	lastMousePos = sf::Mouse::getPosition(window);
	animationSpeed = 2000.0f;
	pause = false;
	showInfo = false;
	syncSpeed = true;
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		keysPressed[i] = false;
		keysProcessed[i] = false;
	}
	leftMouseButtonPressed = false;
	leftMouseButtonProcessed = false;
	info.setFont(ResourceManager::fonts["infoFont"]);
	info.setScale(0.5f, 0.5f);
	info.setPosition(0, 0);
	info.setFillColor(sf::Color::White);
	return true;
}

void Application::initConstant() {

}

void Application::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				sf::Vector2u size = window.getSize();
				cam.resize((float)size.x, (float)size.y);
				defaultView.setCenter(size.x / 2.0f, size.y / 2.0f);
				defaultView.setSize((float)size.x, (float)size.y);
				std::cout << "* Resizing | width: " << size.x << " - height: " << size.y << std::endl;
			}
			if (event.type == sf::Event::KeyPressed) {
				keysPressed[event.key.code] = true;
			}
			if (event.type == sf::Event::KeyReleased) {
				keysPressed[event.key.code] = false;
				keysProcessed[event.key.code] = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					leftMouseButtonPressed = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					leftMouseButtonPressed = false;
					leftMouseButtonProcessed = false;
					ResourceManager::graphs[currentGraph]->unselectAll();
				}
			}
		}
		delta = (deltaClock.restart()).asSeconds();
		inputs();
		update();
		render();
	}
}

void Application::inputs() {
	cam.processInputs(delta);
	currentMousePos = sf::Mouse::getPosition(window);
	if (keysPressed[sf::Keyboard::R] && !keysProcessed[sf::Keyboard::R]) {
		ResourceManager::graphs[currentGraph]->randomizePos(cam.getPosition().x - 400, cam.getPosition().y - 300, 800, 400);
		ResourceManager::graphs[currentGraph]->setHighestSquaredDistance(0.0f);
		keysProcessed[sf::Keyboard::R] = true;
	}
	if (keysPressed[sf::Keyboard::G] && !keysProcessed[sf::Keyboard::G]) {
		ResourceManager::graphs[currentGraph]->clearGraph();
		ResourceManager::generateRandomGraph(currentGraph, 20, 20, (int)cam.getPosition().x - 400, (int)cam.getPosition().y - 300, 800, 600);
		keysProcessed[sf::Keyboard::G] = true;
	}
	if (keysPressed[sf::Keyboard::I] && !keysProcessed[sf::Keyboard::I]) {
		showInfo = !showInfo;
		keysProcessed[sf::Keyboard::I] = true;
	}
	if (keysPressed[sf::Keyboard::O] && !keysProcessed[sf::Keyboard::O]) {
		syncSpeed= !syncSpeed;
		keysProcessed[sf::Keyboard::O] = true;
	}
	if (keysPressed[sf::Keyboard::P] && !keysProcessed[sf::Keyboard::P]) {
		pause = !pause;
		keysProcessed[sf::Keyboard::P] = true;
	}
	if (keysPressed[sf::Keyboard::PageUp] && !keysProcessed[sf::Keyboard::PageUp]) {
		ResourceManager::graphs[currentGraph]->increaseRatio(0.0001f);
		keysProcessed[sf::Keyboard::PageUp] = true;
	}
	if (keysPressed[sf::Keyboard::PageDown] && !keysProcessed[sf::Keyboard::PageDown]) {
		ResourceManager::graphs[currentGraph]->increaseRatio(-0.0001f);
		keysProcessed[sf::Keyboard::PageDown] = true;
	}
	if (leftMouseButtonPressed && !leftMouseButtonProcessed) {
		leftMouseButtonProcessed = true;
		if (!selectNode((int)cam.getPosition().x - (int)(cam.getView().getSize().x / 2), (int)cam.getPosition().y - (int)(cam.getView().getSize().y / 2))) {
			ResourceManager::graphs[currentGraph]->markAll(false);
		}
	}
	else if (leftMouseButtonPressed && leftMouseButtonProcessed) {
		moveSelectedNode();
	}
	lastMousePos = currentMousePos;
}

void Application::update() {
	if (!pause) {
		if (syncSpeed) {
			ResourceManager::graphs[currentGraph]->applyForces2(animationSpeed*delta);
		}
		else {
			ResourceManager::graphs[currentGraph]->applyForces(1.0f);
		}
	}
}

void Application::render() {
	window.clear();
	window.setView(cam.getView());
	Renderer::drawGraph(window, *(ResourceManager::graphs[currentGraph]));
	window.setView(defaultView);
	if (showInfo) {
		window.draw(info);
		sf::String text = sf::String("Paused: " + sf::String(pause ? "true" : "false"));
		text += ("\nDelta: " + std::to_string(ResourceManager::graphs[currentGraph]->getDelta()));
		text += ("\nSpring factor: " + std::to_string(ResourceManager::graphs[currentGraph]->getSpringFactor()));
		text += ("\nSpring rest length: " + std::to_string(ResourceManager::graphs[currentGraph]->getSpringRestLength()));
		text += ("\nRepulsive factor: " + std::to_string(ResourceManager::graphs[currentGraph]->getRepulsiveFactor()));
		text += ("\nRatio: " + std::to_string(ResourceManager::graphs[currentGraph]->getRatio()));
		text += ("\nHighest squared distance: " + std::to_string(ResourceManager::graphs[currentGraph]->getHighestSquaredDistance()));
		text += ("\nAnimation speed: " + std::to_string(animationSpeed));
		text += ("\nSync speed: " + sf::String(syncSpeed ? "true" : "false"));
		text += ("\nMouse x = " + std::to_string(sf::Mouse::getPosition(window).x));
		text += ("\nMouse y = " + std::to_string(sf::Mouse::getPosition(window).y));
		info.setString(text);
	}
	window.display();
}

bool Application::selectNode(int camPosX, int camPosY) {
	NodesRef_Int nodes = ResourceManager::graphs[currentGraph]->getNodes();
	sf::Vector2i worldMousePos(currentMousePos.x + camPosX, currentMousePos.y + camPosY);
	int nodeSize = (int)ResourceManager::nodeRect.getSize().x;
	sf::Rect<int> rect(0, 0, nodeSize, nodeSize);
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		const std::unique_ptr<Node<int>>& node = it->second;
		rect.left = (int)node->getPosX();
		rect.top = (int)node->getPosY();
		if (rect.contains(worldMousePos)) {
			ResourceManager::graphs[currentGraph]->selectNode(node->getLabel(), true);
			// NODE COLORING ResourceManager::graphs[currentGraph]->markNodeAndEdges(node->getLabel(), !(node->isMarked()));
			return true;
		}
	}
	return false;
}

bool Application::moveSelectedNode() {
	sf::Vector2i deltaPos = currentMousePos - lastMousePos;
	NodesRef_Int nodes = ResourceManager::graphs[currentGraph]->getNodes();
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		const std::unique_ptr<Node<int>>& node = it->second;
		if (node->isSelected()) {
			ResourceManager::graphs[currentGraph]->translateNode(node->getLabel(), (float)deltaPos.x, (float)deltaPos.y);
			return true;
		}
	}
	return false;
}
#include "Application.h"

Application::Application() {
	
}

Application::~Application() {

}

void Application::init() {
	window.create(sf::VideoMode(800, 600), "Graph");
	//window.setFramerateLimit(60);
	cam.init(0.0f, 0.0f, 800.0f, 600.0f);
	ResourceManager::loadData();
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
				std::cout << "* Resizing | width: " << size.x << " | height: " << size.y << std::endl;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		ResourceManager::graphs["G1"]->randomizePos(cam.getPosition().x - 200, cam.getPosition().y - 150, 400, 300);
	}
}

void Application::update() {
	ResourceManager::graphs["G1"]->applyForces();
}

void Application::render() {
	window.clear();
	window.setView(cam.getView());
	Renderer::drawGraph(window, *(ResourceManager::graphs["G1"]));
	window.display();
}
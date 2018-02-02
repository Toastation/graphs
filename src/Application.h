#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Camera.h"

class Application {
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;
	Camera cam;
	float delta;
public:
	Application();
	~Application();

	void init();
	void run();
	void inputs();
	void update();
	void render();
};


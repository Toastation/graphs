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
	std::string currentGraph;
	Camera cam;
	float delta;
	float animationSpeed;
	bool pause;
	bool showInfo;
	bool syncSpeed;
	bool keysPressed[sf::Keyboard::KeyCount];
	bool keysProcessed[sf::Keyboard::KeyCount];
	sf::Text info;
public:
	Application();
	~Application();

	bool init();
	void run();
	void inputs();
	void update();
	void render();
};


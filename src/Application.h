#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Camera.h"

class Application {
private:
	sf::RenderWindow window;
	sf::View defaultView;
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
	bool leftMouseButtonPressed;
	bool leftMouseButtonProcessed;
	sf::Text info;
public:
	Application();
	~Application();

	bool init();
	void initConstant();
	void run();
	void inputs();
	void update();
	void render();

	/*
	* @brief mark the node which contains the given coordinates
	* @param x x coordinates to check
	* @param y y coordinates to check
	* @param camPosX x coordinate of the cam, required to convert mouse pos to world pos
	* @param camPosY y coordinate of the cam, required to convert mouse pos to world pos
	* @return whether or not a node has been selected
	*/
	bool selectNode(int x, int y, int camPosX, int camPosY);
};


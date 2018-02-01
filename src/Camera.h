#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

enum Direction {
	UP, DOWN, LEFT, RIGHT
};


const float speed = 250.0f;

class Camera {
private:
	sf::Vector2f position;
	sf::View view;
public:
	Camera();
	~Camera();

	void init(float centerX, float centerY, float width, float height);
	void processInputs(float delta);
	void move(Direction dir, float delta);
	void resize(float width, float height);

	sf::View getView() const { return view; }
	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getSize() const { return view.getSize(); }
};


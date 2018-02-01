#include "Camera.h"

Camera::Camera() {
	position.x = 0.0f;
	position.y = 0.0f;
	view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
}

Camera::~Camera() {

}

void Camera::init(float centerX, float centerY, float width, float height) {
	position.x = centerX;
	position.y = centerY;
	view.setCenter(position);
	resize(width, height);
}

void Camera::processInputs(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		move(LEFT, delta);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move(RIGHT, delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		move(UP, delta);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		move(DOWN, delta);
	}
}

void Camera::move(Direction dir, float delta) {
	switch (dir) {
		case UP:
			position.y -= speed * delta;
			break;
		case DOWN:
			position.y += speed * delta;
			break;
		case LEFT:
			position.x -= speed * delta;
			break;
		case RIGHT:
			position.x += speed * delta;
			break;
		default:
			std::cerr << "Invalid direction" << std::endl;
	}
	view.setCenter(position);
}

void Camera::resize(float width, float height) {
	view.setSize(width, height);
}


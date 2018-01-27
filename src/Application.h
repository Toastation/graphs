#pragma once
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.h"
#include "Graph.h"
#include "Shader.h"

class Application {
private:
	Graph<int> graph;
	glm::mat4 projectionMatrix;
public:
	Application();
	
	void init();
	void update(float delta);
	void render();
};


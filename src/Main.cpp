#include <iostream>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Inputs.h"
#include "Application.h"

#define WIDTH 800
#define HEIGHT 600

/** GLOBAL VARIABLES**/
bool keys[1024];
bool processedKeys[1024];

/** CALLBACK DEFINITION **/
void defaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/*
 * @brief initializes GLFW and set up window hints
 * @return false if the initialization failed
 */
static bool initGLFW() {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "* ERROR: GLFW initialization failed." << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

/*
 * @brief initializes GLEW and set up the necessary OpenGL functions
 * @return false if the initialization failed
 */
static bool initGLEW() {
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK) {
		std::cout << "* ERROR: GLEW initialization failed. Log: " << glewGetErrorString(glewStatus) << std::endl;
		return false;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

/*
 * @brief check if the given window is valid and initializes it
 * @param window the window to check and initialize
 * @return false if the window is invalid or if the initialization failed
 */
static bool checkAndInitializeWindow(GLFWwindow* window) {
	if (!window) {
		glfwTerminate();
		return false;
	}
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window, (mode->width / 2) - (WIDTH / 2), (mode->height / 2) - (HEIGHT / 2));
	glfwSetFramebufferSizeCallback(window, defaultFramebufferSizeCallback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return true;
}

/*
 * @brief terminates all GLFW processes
 */
static void cleanGLFW(GLFWwindow* window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	if (!initGLFW()) {
		return EXIT_FAILURE;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "graph", NULL, NULL);
	if (!checkAndInitializeWindow(window) || !initGLEW()) {
		return EXIT_FAILURE;
	}

	Application app;
	float lastTickTime = 0.0f;
	float delta = 0.0f;


	while (!glfwWindowShouldClose(window)) {
		float currentTickTime = (float)glfwGetTime();
		delta = currentTickTime - lastTickTime;
		lastTickTime = currentTickTime;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		app.update(delta);
		app.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanGLFW(window);
	
	return EXIT_SUCCESS;
}

/** CALLBACKS **/
void defaultFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
			processedKeys[key] = false;
		}
	}
}
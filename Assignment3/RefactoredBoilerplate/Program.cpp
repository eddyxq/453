#include "Program.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RenderingEngine.h"
#include "Scene.h"

Scene* currentScene;
RenderingEngine* renderer;

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);
	currentScene = scene;
	//Main render loop
	while(!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}
	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}

void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (action == GLFW_PRESS) {
		//Program *program = (Program*)glfwGetWindowUserPointer(window);
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			std::cout << "Exiting program." << std::endl;
			break;
		case GLFW_KEY_1: // Quadratic
			std::cout << "Part I: Bezier Curves - Scene I" << std::endl;
			//renderer->degree = 2;
			currentScene->setScene(Scene::QUADRATIC);
			break;
		case GLFW_KEY_2: // Cubic
			std::cout << "Part I: Bezier Curves - Scene II" << std::endl;
			//renderer->degree = 3;
			currentScene->setScene(Scene::CUBIC);
			break;
		case GLFW_KEY_3:
			std::cout << "Part II: Rendering Fonts - Lora" << std::endl;
			currentScene->setScene(Scene::LORA);
			break;
		case GLFW_KEY_4:
			std::cout << "Part II: Rendering Fonts - Source Sans Pro" << std::endl;
			currentScene->setScene(Scene::SOURCE_SANS_PRO);
			break;
		case GLFW_KEY_5:
			std::cout << "Part II: Rendering Fonts - Comic Sans" << std::endl;
			currentScene->setScene(Scene::COMIC_SANS);
			break;
		case GLFW_KEY_6:
			std::cout << "Part III: Scrolling Text - Alex Brush" << std::endl;
			currentScene->setScene(Scene::SCROLLING_ALEX_BRUSH);
			break;
		case GLFW_KEY_7:
			std::cout << "Part III: Scrolling Text - Inconsolata" << std::endl;
			currentScene->setScene(Scene::SCROLLING_INCONSOLATA);
			break;
		case GLFW_KEY_UP:
			currentScene->speedUp();
			break;
		case GLFW_KEY_DOWN:
			currentScene->speedDown();
			break;
		}
	}
}

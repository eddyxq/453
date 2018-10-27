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
	//Set the custom function that tracks cursor position 
	glfwSetCursorPosCallback(window, cursor_position_callback);
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
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			std::cout << "Exiting program." << std::endl;
			break;
		case GLFW_KEY_1: 
			//Part I: Bezier Curves - Scene I"
			currentScene->setScene(Scene::QUADRATIC);
			break;
		case GLFW_KEY_2: 
			//Part I: Bezier Curves - Scene II
			currentScene->setScene(Scene::CUBIC);
			break;
		case GLFW_KEY_3:
			//Part II: Rendering Fonts - Lora
			currentScene->setScene(Scene::LORA);
			break;
		case GLFW_KEY_4:
			//Part II: Rendering Fonts - Source Sans Pro
			currentScene->setScene(Scene::SOURCE_SANS_PRO);
			break;
		case GLFW_KEY_5:
			//Part II: Rendering Fonts - Comic Sans
			currentScene->setScene(Scene::COMIC_SANS);
			break;
		case GLFW_KEY_6:
			//Part III: Scrolling Text - Alex Brush
			currentScene->setScene(Scene::SCROLLING_ALEX_BRUSH);
			break;
		case GLFW_KEY_7:
			//Part III: Scrolling Text - Inconsolata
			currentScene->setScene(Scene::SCROLLING_INCONSOLATA);
			break;
		case GLFW_KEY_8:
			//Part III: Scrolling Text - Zapfino
			currentScene->setScene(Scene::SCROLLING_ZAPFINO);
			break;
		case GLFW_KEY_9:
			//BONUS
			//currentScene->setScene(Scene::BONUS);
			break;
		case GLFW_KEY_RIGHT:
			//increases scroll speed
			currentScene->speedUp();
			break;
		case GLFW_KEY_LEFT:
			//decreases scroll speed
			currentScene->speedDown();
			break;
		}
	}
}

void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	GLboolean leftDown;
	//conditional to track left mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		leftDown = true;
	}
	else {
		leftDown = false;
	}
	//when left botton is held down, do this
	if (leftDown) {
		std::cout << "left clicked" << std::endl;
		
	}
		


	//debugging print statements
	// std::cout << "x: ";
	// std::cout << xpos;
	// std::cout << " y: ";
	// std::cout << ypos << std::endl;

}

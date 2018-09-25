#include "Program.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RenderingEngine.h"
#include "Scene.h"

//Scene* currentScene;
Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

int iteration = 0;
std::string currentScene = "";

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 512;
	int height = 512;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(window, this);
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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	//esc closes the program
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	//press 1 to display part 1 - Squares and Diamonds
	if (key == GLFW_KEY_1 && action == GLFW_PRESS){
		iteration = 0;
		currentScene = "SquaresAndDiamonds";
		program->getScene()->displaySquaresAndDiamondsScene(iteration);
	}
	//press 2 to display part 2 - Parametric Spiral
	if (key == GLFW_KEY_2 && action == GLFW_PRESS){
		iteration = 0;
		currentScene = "ParametricSpiral";
		program->getScene()->displayParametricSpiralScene(iteration);
	}
	//press 3 to display part 3 - Sierpinski Triangles
	if (key == GLFW_KEY_3 && action == GLFW_PRESS){
		iteration = 0;
		currentScene = "Sierpinski";
		program->getScene()->displaySierpinskiScene(iteration);
	}
	//press 4 to display part 4 - Sierpinski Reloaded
	if (key == GLFW_KEY_4 && action == GLFW_PRESS){
		iteration = 0;
		currentScene = "SierpinskiTriangleReloaded";
		program->getScene()->displaySierpinskiTriangleReloadedScene(iteration);
	}
	//press 5 to display part 5 - bonus component
	if (key == GLFW_KEY_5 && action == GLFW_PRESS){
		iteration = 0;
		currentScene = "FractalGeometries";
		program->getScene()->displayFractalGeometriesScene(iteration);
	}
	//press up arrow to increase iteration level
	if (key == GLFW_KEY_UP && action == GLFW_PRESS){
		if (currentScene == "SquaresAndDiamonds"){
			iteration += 1;
			program->getScene()->displaySquaresAndDiamondsScene(iteration);
		}
		else if (currentScene == "ParametricSpiral"){
			iteration += 1;
			program->getScene()->displayParametricSpiralScene(iteration);
		}
		else if (currentScene == "Sierpinski"){
			iteration += 1;
			program->getScene()->displaySierpinskiScene(iteration);
		}
		else if (currentScene == "SierpinskiTriangleReloaded"){
			iteration += 50;
			program->getScene()->displaySierpinskiTriangleReloadedScene(iteration);
		}
	}
	//press down arrow to decrease iteration level
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
		if (currentScene == "SquaresAndDiamonds"){
			iteration -= 1;
			program->getScene()->displaySquaresAndDiamondsScene(iteration);
		}
		else if (currentScene == "ParametricSpiral"){
			iteration -= 1;
			program->getScene()->displayParametricSpiralScene(iteration);
		}
		else if (currentScene == "Sierpinski"){
			iteration -= 1;
			program->getScene()->displaySierpinskiScene(iteration);
		}
		else if (currentScene == "SierpinskiTriangleReloaded"){
			iteration -= 50;
			program->getScene()->displaySierpinskiTriangleReloadedScene(iteration);
		}
	}
}
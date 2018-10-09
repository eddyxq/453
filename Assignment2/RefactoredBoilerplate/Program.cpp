/*
* Program.cpp
*
*  Created on: Sep 10, 2018
*      Author: John Hall
*/

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

int num;
bool changeImage;

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
	renderer = renderingEngine;
	//num = scene->getImageNum();
	//Main render loop
	while (!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (changeImage) {
			scene->refresh(num);
			changeImage = false;
		}
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

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Set the custom function that tracks scroll wheel 
	glfwSetScrollCallback(window, scroll_callback);

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
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//press number keys from 1 to 7 to display each of the 7 images
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		num = 1;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		num = 2;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		num = 3;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		num = 4;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		num = 5;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		num = 6;
		changeImage = true;
		renderer->l = 0;
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		num = 7;
		changeImage = true;
		renderer->l = 0;
	}
	//press number keys 8, 9, 0 to apply shaders
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) 
	{
		renderer->l = 1;
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) 
	{
		renderer->l = 2;
	}
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) 
	{
		renderer->l = 3;
	}
	//press s to apply a sepia tone
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		renderer->l = 4;
	}
	//press a to rotate counter clockwise
	if (key == GLFW_KEY_A && action == GLFW_PRESS) 
	{
		renderer->degree += 45;
	}
	//press a to rotate clockwise
	if (key == GLFW_KEY_D && action == GLFW_PRESS) 
	{
		renderer->degree -= 45;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//scroll forward to zoom in
	if (yoffset == 1) 
	{
		renderer->zoom += 1;
	}
	//scroll backward to zoom out
	else if (yoffset == -1)
	{
		if (renderer->zoom > 1)
		{
			renderer->zoom -= 1;
		}
	}
}

double rx;
double ry;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	GLboolean leftDown;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		leftDown = true;
	}
	else 
	{
		leftDown = false;
	}
	if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
	{
		rx = xpos;
		ry = ypos;
	}
	if (leftDown)
	{
		renderer->cursor_y = (ypos-ry)/-512/2;
		renderer->cursor_x = (xpos-rx)/512/2;
	}
}

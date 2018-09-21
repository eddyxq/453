/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
     displaySquaresAndDiamondsScene(0);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::displaySquaresAndDiamondsScene(int iteration) {

	objects.clear();
	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry square;

	float postiveBorderValue = 0.9f;
	float negativeBorderValue = -0.9f;

	//float iteration = 6;
	float scalingFactor = 1;
	double shadeFactor = 1;

	for (int x = 0; x < iteration; x++) {
		//squares
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		//diamonds
		square.verts.push_back(glm::vec3(-0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, -0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, 0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, 0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, -0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));

		scalingFactor *= 2;
	}

	for (int i = 0; i < iteration; i++) {
		for (int j = 0; j < 8; j++) {
			square.colors.push_back(glm::vec3(shadeFactor, 0.0f, 0.0f));
		}

		for (int k = 0; k < 8; k++) {
			square.colors.push_back(glm::vec3(0.0f, shadeFactor, 0.0f));
		}
		shadeFactor -= 0.2;
	}

	square.drawMode = GL_LINES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(square);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(square);

	//Add the triangle to the scene objects
	objects.push_back(square);
}

void Scene::displayParametricSprialScene(int iteration){
	objects.clear();

	//Our circle object
	Geometry circle;

	//RGB color parameters
	double r = 1;
	double g = 0;
	double b = 0;

	int numberOfLineSegments = 100;
	float du = 2 * 3.14f / numberOfLineSegments;
	for (float u = 0; u < iteration * 2 * 3.14f; u += du)
	{
		double xCoord = 0.038 * u * cos(u); //1 is important, change to something else for spiral
		double yCoord = 0.038 * u * sin(u);
		double zCoord = 1.0f;

		circle.verts.push_back(glm::vec3(xCoord, yCoord, zCoord));
		circle.colors.push_back(glm::vec3(r, g, b));
	
		//Creates a color gradient from red to green
		r -= 0.0015;
		g += 0.0015;
	}
	//Renders the line connecting any 2 points drawn
	circle.drawMode = GL_LINE_STRIP;	
	
	//Construct VAO and VBOs for the circle
	RenderingEngine::assignBuffers(circle);
	RenderingEngine::setBufferData(circle);
	objects.push_back(circle);
}

void Scene::displayMengerSpongeScene(int iteration) {

}

void Scene::displaySierpinskiTriangleReloadedScene(int iteration) {

}

void Scene::displayFractalGeometriesScene(int iteration) {

}
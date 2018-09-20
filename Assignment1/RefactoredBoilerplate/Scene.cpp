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
     displaySquaresAndDiamondsScene();
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::displaySquaresAndDiamondsScene() {

	objects.clear();
	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry triangle;
	triangle.verts.push_back(glm::vec3(-0.6f, -0.4f, 1.0f));
	triangle.verts.push_back(glm::vec3(0.0f, 0.6f, 1.0f));
	triangle.verts.push_back(glm::vec3(0.6f, -0.4f, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	triangle.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	triangle.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	triangle.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	triangle.drawMode = GL_TRIANGLES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(triangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(triangle);

	//Add the triangle to the scene objects
	objects.push_back(triangle);
}

void Scene::displayParametricSprialScene(int x){
	objects.clear();

	//Our circle object
	Geometry circle;

	//RGB color parameters
	float r = 1;
	float g = 0;
	float b = 0;

	int numberOfLineSegments = 100;
	float du = 2 * 3.14f / numberOfLineSegments;
	for (float u = 0; u < x * 3.14f; u += du)
	{
		float xCoord = 0.038 * u * cos(u); //1 is important, change to something else for spiral
		float yCoord = 0.038 * u * sin(u);
		float zCoord = 1.0f;

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

void Scene::displayMengerSpongeScene() {

}

void Scene::displaySierpinskiTriangleReloadedScene() {

}

void Scene::displayFractalGeometriesScene() {

}
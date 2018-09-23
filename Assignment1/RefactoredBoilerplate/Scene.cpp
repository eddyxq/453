/*
 * This class contains the scenes
 * @author Eddy Qiang - CPSC 453 - Tutorial T01
 * @version 1.2 
 * @since September 20, 2018
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
	Geometry square;
	float scalingFactor = 1;
	double shadeFactor = 1;
	//Create the squares and diamonds
	for (int x = 0; x < iteration; x++) {
		//Squares
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, 0.9f/scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f/scalingFactor, -0.9f/scalingFactor, 1.0f));
		//Diamonds
		square.verts.push_back(glm::vec3(-0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, -0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, 0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(-0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, 0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.0f /scalingFactor, -0.9f /scalingFactor, 1.0f));
		square.verts.push_back(glm::vec3(0.9f /scalingFactor, 0.0f /scalingFactor, 1.0f));
		//Adjust scaling factor to fit nested shapes
		scalingFactor *= 2;
	}
	//Color the lines
	for (int i = 0; i < iteration; i++) {
		for (int j = 0; j < 8; j++) {
			square.colors.push_back(glm::vec3(shadeFactor, 0.0f, 0.0f));
		}

		for (int k = 0; k < 8; k++) {
			square.colors.push_back(glm::vec3(0.0f, shadeFactor, 0.0f));
		}
		//Adjust shade factore to create gradient
		shadeFactor -= 0.2;
	}
	//Set draw mode
	square.drawMode = GL_LINES;
	//Construct vao and vbos 
	RenderingEngine::assignBuffers(square);
	//Send square data to the GPU
	RenderingEngine::setBufferData(square);
	//Add sqaure to scene objects
	objects.push_back(square);
}

void Scene::displayParametricSprialScene(int iteration){
	objects.clear();
	Geometry circle;
	//RGB color parameters
	double r = 1;
	double g = 0;
	double b = 0;
	int numberOfLineSegments = 100;
	float du = 2 * 3.14f / numberOfLineSegments;
	//Create spirals
	for (float u = 0; u < iteration * 2 * 3.14f; u += du) {
		double xCoord = 0.038 * u * cos(u); 
		double yCoord = 0.038 * u * sin(u);
		double zCoord = 1.0f;
		circle.verts.push_back(glm::vec3(xCoord, yCoord, zCoord));
		circle.colors.push_back(glm::vec3(r, g, b));
		//Creates a color gradient from red to green
		r -= 0.0015;
		g += 0.0015;
	}
	//Set draw mode
	circle.drawMode = GL_LINE_STRIP;	
	//Construct VAO and VBOs 
	RenderingEngine::assignBuffers(circle);
	RenderingEngine::setBufferData(circle);
	objects.push_back(circle);
}

void Scene::displaySierpinskiScene(int iteration) {
	objects.clear();
	Geometry triangle;
	float x1 = 0.0f; float y1 = sqrt(pow(0.9, 2) - pow(0.45, 2));
	float x2 = 0.9f; float y2 = -0.9f;
	float x3 = -0.9f; float y3 = -0.9f;

	float r = 1.0f; float g = 1.0f; float b = 1.0f;

	drawSierpinski(x1, y1, x2, y2, x3, y3, triangle, iteration, r, g, b);
}

void Scene::displaySierpinskiTriangleReloadedScene(int iteration) {

}

void Scene::displayFractalGeometriesScene(int iteration) {

}

void Scene::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int iteration, float r, float g, float b)
{
	Geometry triangle;

	triangle.verts.push_back(glm::vec3(x1, y1, 1.0f));
	triangle.verts.push_back(glm::vec3(x2, y2, 1.0f));
	triangle.verts.push_back(glm::vec3(x3, y3, 1.0f));

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


void Scene::drawSierpinski(float x1, float y1, float x2, float y2, float x3, float y3, Geometry triangle, int iteration, float r, float g, float b)
{
	drawTriangle(x1, y1, x2, y2, x3, y3, iteration, r, g, b);
	if (iteration > 0)
	{
		float ax = (x1 + x2) / 2; float ay = (y1 + y2) / 2;
		float bx = (x2 + x3) / 2; float by = (y2 + y3) / 2;
		float cx = (x1 + x3) / 2; float cy = (y1 + y3) / 2;
		drawSierpinski(x1, y1, ax, ay, cx, cy, triangle, iteration - 1, 1, 0, 0);
		drawSierpinski(ax, ay, x2, y2, bx, by, triangle, iteration - 1, 0, 1, 0);
		drawSierpinski(cx, cy, bx, by, x3, y3, triangle, iteration - 1, 0, 0, 1);
	}
}
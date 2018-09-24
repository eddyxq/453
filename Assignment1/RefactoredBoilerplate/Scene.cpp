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
	//base triangle coordinates
	double x1 = 0.0f;     double y1 = sqrt(pow(0.9, 2) - pow(0.45, 2));
	double x2 = 0.45f;    double y2 = (y1-0.9)/2;
	double x3 = -0.45f;   double y3 = (y1-0.9)/2;

	//top blue triangle
	double a_x1 = 0.0f;   double a_y1 = sqrt(pow(0.9, 2) - pow(0.45, 2));
	double a_x2 = 0.45f;  double a_y2 = (y1-0.9)/2;
	double a_x3 = -0.45f; double a_y3 = (y1-0.9)/2;
	drawSierpinski(a_x1, a_y1, a_x2, a_y2, a_x3, a_y3, triangle, iteration, 0, 0, 1);

	//bottom right green triangle
	double b_x1 = 0.45f;  double b_y1 = (y1-0.9)/2;
	double b_x2 = 0.9f;   double b_y2 = -0.9f;
	double b_x3 = 0.0f;   double b_y3 = -0.9f;
	drawSierpinski(b_x1, b_y1, b_x2, b_y2, b_x3, b_y3, triangle, iteration, 0, 1, 0);

	//bottom left red triangle
	double c_x1 = -0.45f; double c_y1 = (y1-0.9)/2;
	double c_x2 = 0.0f;   double c_y2 = -0.9f;
	double c_x3 = -0.9f;  double c_y3 = -0.9f;
	drawSierpinski(c_x1, c_y1, c_x2, c_y2, c_x3, c_y3, triangle, iteration, 1, 0, 0);
}

void Scene::displaySierpinskiTriangleReloadedScene(int iteration) {

}

void Scene::displayFractalGeometriesScene(int iteration) {

}

void Scene::drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int iteration, double r, double g, double b)
{
	Geometry triangle;

	triangle.verts.push_back(glm::vec3(x1, y1, 1.0f));
	triangle.verts.push_back(glm::vec3(x2, y2, 1.0f));
	triangle.verts.push_back(glm::vec3(x3, y3, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	triangle.colors.push_back(glm::vec3(r, g, b));
	triangle.colors.push_back(glm::vec3(r, g, b));
	triangle.colors.push_back(glm::vec3(r, g, b));

	triangle.drawMode = GL_TRIANGLES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(triangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(triangle);

	//Add the triangle to the scene objects
	objects.push_back(triangle);
}

void Scene::drawSierpinski(double x1, double y1, double x2, double y2, double x3, double y3, Geometry triangle, int iteration, double r, double g, double b)
{
	drawTriangle(x1, y1, x2, y2, x3, y3, iteration, r, g, b);
	if (iteration > 0)
	{
		double ax = (x1 + x2) / 2; double ay = (y1 + y2) / 2;
		double bx = (x2 + x3) / 2; double by = (y2 + y3) / 2;
		double cx = (x1 + x3) / 2; double cy = (y1 + y3) / 2;
		r -= 0.05; g -= 0.05; b -= 0.05;
		drawSierpinski(x1, y1, ax, ay, cx, cy, triangle, iteration - 1, r, g, b); 
		r -= 0.05; g -= 0.05; b -= 0.05;
		drawSierpinski(ax, ay, x2, y2, bx, by, triangle, iteration - 1, r, g, b); 
		r -= 0.05; g -= 0.05; b -= 0.05;
		drawSierpinski(cx, cy, bx, by, x3, y3, triangle, iteration - 1, r, g, b); 
	}
}
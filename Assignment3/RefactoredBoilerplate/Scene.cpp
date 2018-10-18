/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlyphExtractor.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	spiral.verts.push_back(glm::vec3( 1.0f, 0.0f, 1.0f)); //same here 3 for quad 4 for cubic
	spiral.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	spiral.verts.push_back(glm::vec3( 0.0f, 1.0f, 1.0f));

	spiral.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 1.0f, 1.0f, 0.0f));
	spiral.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));

	spiral.drawMode = GL_PATCHES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the triangle to the scene objects
	objects.push_back(spiral);

	/*
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	MyGlyph a = g.ExtractGlyph('a');

	for (unsigned int i = 0; i < a.contours.size(); i++) {
		std::cout << "Contour " << i << std::endl;
		for(unsigned int j = 0; j < a.contours[i].size(); j++) {
			std::cout << "Bezier curve " << j << std::endl;
			for(unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				std::cout << "x " << a.contours[i][j].x[k] << std::endl;
				std::cout << "y " << a.contours[i][j].y[k] << std::endl;
				std::cout << std::endl;
			}
		}
	}
	*/
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}


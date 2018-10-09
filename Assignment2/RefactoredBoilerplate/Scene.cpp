/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"
#include <string>
#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

MyTexture texture, texture2, texture3, texture4, texture5, texture6, texture7;


Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	//initialize all the images
	InitializeTexture(&texture, "image1-mandrill.png", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture2, "image2-uclogo.png", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture3, "image3-aerial.jpg", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture4, "image4-thirsk.jpg", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture5, "image5-pattern.png", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture6, "image6-bubble.png", GL_TEXTURE_RECTANGLE);
	InitializeTexture(&texture7, "image7-hourglass.png", GL_TEXTURE_RECTANGLE);

	glUseProgram(renderer->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	glUniform1i(uniformLocation, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::refresh(int num)
{
	RenderingEngine::deleteBufferData(rectangle);
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();
	MyTexture current_texture;

	if (num == 1)
	{
		current_texture = texture;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	}
	else if (num == 2)
	{
		current_texture = texture2;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture2.textureID);
	}
	else if (num == 3)
	{
		current_texture = texture3;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture3.textureID);
	}
	else if (num == 4)
	{
		current_texture = texture4;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture4.textureID);
	}
	else if (num == 5)
	{
		current_texture = texture5;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture5.textureID);
	}
	else if (num == 6)
	{
		current_texture = texture6;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture6.textureID);
	}
	else if (num == 7)
	{
		current_texture = texture7;
		glBindTexture(GL_TEXTURE_RECTANGLE, texture7.textureID);
	}

	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));
	rectangle.drawMode = GL_TRIANGLES;
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(current_texture.width), 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(current_texture.width), float(current_texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(current_texture.width), float(current_texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(current_texture.height)));
	RenderingEngine::assignBuffers(rectangle);
	RenderingEngine::setBufferData(rectangle);
	objects.push_back(rectangle);
}

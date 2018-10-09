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

#include "texture.h"

#include <iomanip>

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	InitializeTexture(&fgTexture, FG_IMG2, GL_TEXTURE_RECTANGLE);
	InitializeTexture(&bgTexture, BG_IMG3, GL_TEXTURE_RECTANGLE);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	objects.clear();
	//Load texture uniform
	//Shaders need to be active to load uniforms
	glUseProgram(renderer->shaderProgram);
	//Set which texture unit the texture is bound to
	glActiveTexture(GL_TEXTURE1);
	//Bind the texture to GL_TEXTURE0
	glBindTexture(GL_TEXTURE_RECTANGLE, fgTexture.textureID);
	//Get identifier for uniform
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");

	//Load texture unit number into uniform
	glUniform1i(uniformLocation, 1);

	std::vector<GLfloat> gaussian5 = gaussian1D(7);
	GLfloat filter[49];
	for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) {
		filter[7 * j + i] = gaussian5[i] * gaussian5[j];
	}

	GLuint filterKernelLoc = glGetUniformLocation(renderer->shaderProgram, "filterKernel");
	GLuint kSizeLoc = glGetUniformLocation(renderer->shaderProgram, "kSize");
	glUniform1fv(filterKernelLoc, 49, filter);
	glUniform1i(kSizeLoc, 7);

	if (renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.0f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, 0.0f, 1.0f));

	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(fgTexture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(fgTexture.height)));

	RenderingEngine::assignBuffers(rectangle);

	//Send the rectangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	objects.push_back(rectangle);
	renderer->RenderScene(objects);
}

void Scene::updateBackground(int idx) {
	glUseProgram(renderer->shaderProgram2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, bgTexture.textureID);

	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram2, "bgTexture");
	glUniform1i(uniformLocation, 0);

	Geometry rectangle;
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	rectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(bgTexture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(bgTexture.height)));

	rectangle.drawMode = GL_TRIANGLES;

	renderer->assignBuffers(rectangle);
	renderer->setBufferData(rectangle);
	glBindVertexArray(rectangle.vao);
	glDrawArrays(GL_TRIANGLES, 0, rectangle.verts.size());
	glBindVertexArray(0);

	renderer->RenderBackground(rectangle);
}

void Scene::switchScene(int idx) {
	GLuint filterKernelLoc = glGetUniformLocation(renderer->shaderProgram, "filterKernel");
	GLuint kSizeLoc = glGetUniformLocation(renderer->shaderProgram, "kSize");
	switch (idx) {
	case 0:
		glUniform1fv(filterKernelLoc, 1, identity);
		glUniform1i(kSizeLoc, 1);
		break;
	case 1:
		glUniform1fv(filterKernelLoc, 9, vertical_sobel);
		glUniform1i(kSizeLoc, 3);
		break;
	case 2:
		glUniform1fv(filterKernelLoc, 9, horizontal_sobel);
		glUniform1i(kSizeLoc, 3);
		break;
	case 3:
		glUniform1fv(filterKernelLoc, 9, unsharpen_mask);
		glUniform1i(kSizeLoc, 3);
		break;
	case 4:
		
		break;
	default:
		break;
	}
	RenderingEngine::setBufferData(rectangle);
}

std::vector<GLfloat> Scene::gaussian1D(int n) {
	std::vector<GLfloat> ret(n);
	// assumes sigma = 1
	double area = std::erf(n / 2.0 / std::sqrt(2));
	for (int i = 0; i <= n / 2; i++) {
		double u = (i + 0.5) / std::sqrt(2);
		double l = (i - 0.5) / std::sqrt(2);
		ret[n / 2 + i] = ret[n / 2 - i] =
			(GLfloat)(0.5 * (std::erf(u) - std::erf(l)) / area);
	}
	return ret;
}


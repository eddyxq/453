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
	for (std::string file : fgImages) {
		MyTexture texture;
		InitializeTexture(&texture, file.c_str(), GL_TEXTURE_RECTANGLE);
		foregrounds.push_back(texture);
	}
	for (std::string file : bgImages) {
		MyTexture texture;
		InitializeTexture(&texture, file.c_str(), GL_TEXTURE_RECTANGLE);
		backgrounds.push_back(texture);
	}
	fgTexture = foregrounds[0];
	bgTexture = backgrounds[0];
}

Scene::~Scene() {

}

void Scene::displayScene() {
	RenderingEngine::deleteBufferData(fgRectangle);
	fgRectangle.verts.clear();
	fgRectangle.uvs.clear();
	RenderingEngine::deleteBufferData(bgRectangle);
	bgRectangle.verts.clear();
	bgRectangle.uvs.clear();

	glUseProgram(renderer->shaderProgram2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, bgTexture.textureID);

	GLuint bgLoc = glGetUniformLocation(renderer->shaderProgram2, "bgTexture");
	glUniform1i(bgLoc, 0);

	bgRectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	bgRectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	bgRectangle.uvs.push_back(glm::vec2(float(bgTexture.width), 0.f));
	bgRectangle.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	bgRectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	bgRectangle.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	bgRectangle.uvs.push_back(glm::vec2(0.0f, float(bgTexture.height)));

	bgRectangle.drawMode = GL_TRIANGLES;
	renderer->RenderBackground(bgRectangle);

	glUseProgram(renderer->shaderProgram);
	selectFilter();

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_RECTANGLE, fgTexture.textureID);

	GLuint fgLoc = glGetUniformLocation(renderer->shaderProgram, "fgTexture");
	glUniform1i(fgLoc, 1);

	fgRectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	fgRectangle.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	fgRectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	fgRectangle.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	fgRectangle.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	fgRectangle.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	fgRectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	fgRectangle.uvs.push_back(glm::vec2(float(fgTexture.width), 0.f));
	fgRectangle.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	fgRectangle.uvs.push_back(glm::vec2(0.0f, 0.0f));
	fgRectangle.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	fgRectangle.uvs.push_back(glm::vec2(0.0f, float(fgTexture.height)));

	fgRectangle.drawMode = GL_TRIANGLES;

	renderer->assignBuffers(fgRectangle);
	renderer->setBufferData(fgRectangle);
	glBindVertexArray(fgRectangle.vao);
	glDrawArrays(fgRectangle.drawMode, 0, fgRectangle.verts.size());

	renderer->RenderScene({ fgRectangle });
}

void Scene::selectFilter(int idx) {
	sceneIdx = idx;
}

void Scene::selectFilter() {
	GLuint filterKernelLoc = glGetUniformLocation(renderer->shaderProgram, "filterKernel");
	GLuint kSizeLoc = glGetUniformLocation(renderer->shaderProgram, "kSize");
	std::vector<GLfloat> bgRectangle = { 0.155f, 0.22f, 0.25f, 0.22f, 0.155f };
	switch (sceneIdx) {
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
	case 5:
	case 6:
		GLfloat filter[25];
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) {
			filter[5 * j + i] = bgRectangle[i] * bgRectangle[j];
		}
		glUniform1fv(filterKernelLoc, 25, filter);
		glUniform1i(kSizeLoc, 5);
		break;
	default:
		break;
	}
}

void Scene::selectForeground(int idx) {
	fgTexture = foregrounds[idx];
}

void Scene::selectBackground(int idx) {
	bgTexture = backgrounds[idx];
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


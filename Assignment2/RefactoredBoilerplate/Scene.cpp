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

Scene::Scene(RenderingEngine* renderer) : renderer(renderer), sceneIdx(1) {
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
	fgTexture = foregrounds[1];
	bgTexture = backgrounds[2];
}

Scene::~Scene() {

}

void Scene::displayScene() {
	glUseProgram(renderer->shaderProgram2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, bgTexture.textureID);

	GLuint bgLoc = glGetUniformLocation(renderer->shaderProgram2, "bgTexture");
	glUniform1i(bgLoc, 0);
	Geometry g1;
	g1.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g1.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	g1.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g1.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g1.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g1.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	g1.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g1.uvs.push_back(glm::vec2(float(bgTexture.width), 0.f));
	g1.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	g1.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g1.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	g1.uvs.push_back(glm::vec2(0.0f, float(bgTexture.height)));

	g1.drawMode = GL_TRIANGLES;
	renderer->RenderBackground(g1);

	glUseProgram(renderer->shaderProgram);
	selectFilter();

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_RECTANGLE, fgTexture.textureID);

	GLuint fgLoc = glGetUniformLocation(renderer->shaderProgram, "fgTexture");
	glUniform1i(fgLoc, 1);

	Geometry g2;
	g2.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	g2.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g2.uvs.push_back(glm::vec2(float(fgTexture.width), 0.f));
	g2.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	g2.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g2.uvs.push_back(glm::vec2(float(fgTexture.width), float(fgTexture.height)));
	g2.uvs.push_back(glm::vec2(0.0f, float(fgTexture.height)));

	g2.drawMode = GL_TRIANGLES;

	renderer->assignBuffers(g2);
	renderer->setBufferData(g2);
	glBindVertexArray(g2.vao);
	glDrawArrays(g2.drawMode, 0, g2.verts.size());

	renderer->RenderScene({ g2 });
}

void Scene::selectFilter(int idx) {
	sceneIdx = idx;
}

void Scene::selectFilter() {
	GLuint filterKernelLoc = glGetUniformLocation(renderer->shaderProgram, "filterKernel");
	GLuint kSizeLoc = glGetUniformLocation(renderer->shaderProgram, "kSize");
	std::vector<GLfloat> g1 = { 0.155f, 0.22f, 0.25f, 0.22f, 0.155f };
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
		GLfloat filter[25];
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) {
			filter[5 * j + i] = g1[i] * g1[j];
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


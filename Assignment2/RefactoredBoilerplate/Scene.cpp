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

	bgRectangle.verts.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	bgRectangle.verts.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));

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

	fgRectangle.verts.insert(fgRectangle.verts.end(), fgVertices.begin(), fgVertices.end());

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

void Scene::updateVertices(float x, float y, float degree) {
	const double PI = std::atan(1) * 4;
	for (glm::vec3& v : fgVertices) {
		v.x += x - prevX;
		v.y += y - prevY;
		float cx = v.x, cy = v.y;
		double angle = PI * (degree - prevDeg) / 180.0f;
		v.y = std::sin(angle)*cx + std::cos(angle)*cy;
		v.x = std::cos(angle)*cx - std::sin(angle)*cy;
	}
	prevX = x, prevY = y, prevDeg = degree;
}

void Scene::updateZoom(float zoom) {
	for (glm::vec3& v : fgVertices) {
		v.x *= (zoom / prevZoom);
		v.y *= (zoom / prevZoom);
	}
	prevZoom = zoom;
}

void Scene::stopVerticesUpdate() {
	prevX = 0.0f, prevY = 0.0f, prevDeg = 0.0f;
}

void Scene::selectFilter(int idx) {
	sceneIdx = idx;
}

void Scene::selectFilter() {
	GLuint filterKernelLoc = glGetUniformLocation(renderer->shaderProgram, "filterKernel");
	GLuint kSizeLoc = glGetUniformLocation(renderer->shaderProgram, "kSize");
	std::vector<GLfloat> gaussianFilter3 = { 0.315f, 0.36f, 0.315f };
	std::vector<GLfloat> gaussianFilter5 = { 0.155f, 0.22f, 0.25f, 0.22f, 0.155f };
	std::vector<GLfloat> gaussianFilter7 = { 0.07f, 0.13f, 0.19f, 0.21f, 0.19f, 0.13f, 0.07f};
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
		GLfloat filter3[9];
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
			filter3[3 * j + i] = gaussianFilter3[i] * gaussianFilter3[j];
		}
		glUniform1fv(filterKernelLoc, 9, filter3);
		glUniform1i(kSizeLoc, 3);
		break;
	case 5:
		GLfloat filter5[25];
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) {
			filter5[5 * j + i] = gaussianFilter5[i] * gaussianFilter5[j];
		}
		glUniform1fv(filterKernelLoc, 25, filter5);
		glUniform1i(kSizeLoc, 5);
		break;
	case 6:
		GLfloat filter7[49];
		for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) {
			filter7[7 * j + i] = gaussianFilter7[i] * gaussianFilter7[j];
		}
		glUniform1fv(filterKernelLoc, 49, filter7);
		glUniform1i(kSizeLoc, 7);
		break;
	default:
		break;
	}
}

void Scene::selectForeground(int idx) {
	fgTexture = foregrounds[idx];
	fgVertices.clear();
	if (fgTexture.width <= fgTexture.height) {
		float ratio = float(fgTexture.width) / float(fgTexture.height);
		fgVertices.push_back(glm::vec3(ratio * -1.0f, -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(ratio * 1.0f, -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(ratio * 1.0f, 1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(ratio * -1.0f, -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(ratio * 1.0f, 1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(ratio * -1.0f, 1.0f, 1.0f));
	}
	else {
		float ratio = float(fgTexture.height) / float(fgTexture.width);
		fgVertices.push_back(glm::vec3(-1.0f, ratio * -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(1.0f, ratio * -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(1.0f, ratio * 1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(-1.0f, ratio * -1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(1.0f, ratio * 1.0f, 1.0f));
		fgVertices.push_back(glm::vec3(-1.0f, ratio * 1.0f, 1.0f));
	}
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


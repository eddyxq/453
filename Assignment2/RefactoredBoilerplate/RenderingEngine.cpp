/*
 * RenderingEngine.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "RenderingEngine.h"

#include <iostream>

//cpp file purposely included here because it just contains some global functions
#include "ShaderTools.h"

#include "texture.h"

RenderingEngine::RenderingEngine() {
	shaderProgram = ShaderTools::InitializeShaders("../shaders/fragment.glsl");
	shaderProgram2 = ShaderTools::InitializeShaders("../shaders/fragment2.glsl");
	if (shaderProgram == 0) {
		std::cout << "Program could not initialize shaders, TERMINATING" << std::endl;
		return;
	}
	time = 1;
	location = glGetUniformLocation(shaderProgram, "time");
	time++;
}

RenderingEngine::~RenderingEngine() {

}

void RenderingEngine::RenderBackground(const Geometry& bg) {
	glUseProgram(shaderProgram2);

	glBindVertexArray(bg.vao);
	glDrawArrays(bg.drawMode, 0, bg.verts.size());
	deleteBufferData(bg);
	glBindVertexArray(0);

	glUseProgram(0);
}

void RenderingEngine::RenderScene(const std::vector<Geometry>& objects) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// bind our shader program and the vertex array object containing our
	// scene geometry, then tell OpenGL to draw our geometry
	glUseProgram(shaderProgram2);
	MyTexture bgTexture;
	InitializeTexture(&bgTexture, "background3-wood.jpg", GL_TEXTURE_RECTANGLE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, bgTexture.textureID);

	GLuint uniformLocation = glGetUniformLocation(shaderProgram2, "bgTexture");
	glUniform1i(uniformLocation, 0);

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

	assignBuffers(g1);
	setBufferData(g1);
	glBindVertexArray(g1.vao);
	glDrawArrays(g1.drawMode, 0, g1.verts.size());

	glUseProgram(shaderProgram);

	MyTexture fgTexture;
	InitializeTexture(&fgTexture, "image2-uclogo.png", GL_TEXTURE_RECTANGLE);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_RECTANGLE, fgTexture.textureID);

	GLuint fgLoc = glGetUniformLocation(shaderProgram, "fgTexture");
	glUniform1i(fgLoc, 1);

	Geometry g2;
	g2.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(-0.9f, -0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(0.9f, 0.9f, 1.0f));
	g2.verts.push_back(glm::vec3(-0.9f, 0.9f, 1.0f));

	g2.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g2.uvs.push_back(glm::vec2(float(bgTexture.width), 0.f));
	g2.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	g2.uvs.push_back(glm::vec2(0.0f, 0.0f));
	g2.uvs.push_back(glm::vec2(float(bgTexture.width), float(bgTexture.height)));
	g2.uvs.push_back(glm::vec2(0.0f, float(bgTexture.height)));

	g2.drawMode = GL_TRIANGLES;

	assignBuffers(g2);
	setBufferData(g2);
	glBindVertexArray(g2.vao);
	glDrawArrays(g2.drawMode, 0, g2.verts.size());

	glUniform1i(location, time);

	//for (const Geometry& g : objects) {
	//	glBindVertexArray(g.vao);
	//	glDrawArrays(g.drawMode, 0, g.verts.size());
	//	deleteBufferData(g);

	//	// reset state to default (no shader or geometry bound)
	//	glBindVertexArray(0);
	//}

	glUseProgram(0);

	// check for an report any OpenGL errors
	CheckGLErrors();
}

void RenderingEngine::assignBuffers(Geometry& geometry) {
	//Generate vao for the object
	//Constant 1 means 1 vao is being generated
	glGenVertexArrays(1, &geometry.vao);
	glBindVertexArray(geometry.vao);

	//Generate vbos for the object
	//Constant 1 means 1 vbo is being generated
	glGenBuffers(1, &geometry.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	//Parameters in order: Index of vbo in the vao, number of primitives per element, primitive type, etc.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*glGenBuffers(1, &geometry.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);*/

	if (!geometry.colors.empty()) {
		glGenBuffers(1, &geometry.colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
		//Parameters in order: Index of vbo in the vao, number of primitives per element, primitive type, etc.
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	glGenBuffers(1, &geometry.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);


}

void RenderingEngine::setBufferData(Geometry& geometry) {
	//Send geometry to the GPU
	//Must be called whenever anything is updated about the object
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.verts.size(), geometry.verts.data(), GL_STATIC_DRAW);

	/*glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.normals.size(), geometry.normals.data(), GL_STATIC_DRAW);*/

	if (!geometry.colors.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.colors.size(), geometry.colors.data(), GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * geometry.uvs.size(), geometry.uvs.data(), GL_STATIC_DRAW);
}

void RenderingEngine::deleteBufferData(const Geometry& geometry) {
	glDeleteBuffers(1, &geometry.vertexBuffer);
	glDeleteBuffers(1, &geometry.normalBuffer);
	glDeleteBuffers(1, &geometry.colorBuffer);
	glDeleteBuffers(1, &geometry.uvBuffer);
	glDeleteVertexArrays(1, &geometry.vao);
}

bool RenderingEngine::CheckGLErrors() {
	bool error = false;
	for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
	{
		std::cout << "OpenGL ERROR:  ";
		switch (flag) {
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM" << std::endl; break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE" << std::endl; break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION" << std::endl; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
		default:
			std::cout << "[unknown error code]" << std::endl;
		}
		error = true;
	}
	return error;
}

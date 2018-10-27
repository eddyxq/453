#include "RenderingEngine.h"
#include <iostream>
#include "ShaderTools.h"

RenderingEngine::RenderingEngine() {
	shaderProgramCurves = ShaderTools::InitializeShaders();
	shaderProgramNoTesselation = ShaderTools::InitializeShaders2();
	dx = 0.0f;
	degreeLocation = glGetUniformLocation(shaderProgramCurves, "degree");
	dxCurvesLocation = glGetUniformLocation(shaderProgramCurves, "dx");
	dxNoTesselationLocation = glGetUniformLocation(shaderProgramNoTesselation, "dx");
}

RenderingEngine::~RenderingEngine() {

}

void RenderingEngine::RenderControlLines(const std::vector<Geometry>& objects)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramNoTesselation);
	glUniform1f(dxNoTesselationLocation, dx);
	for (const Geometry& g : objects) {
		if (g.controlPointsPerCurve > 0) {
			for (unsigned int min = 0; min <= g.verts.size() - g.controlPointsPerCurve; min += g.controlPointsPerCurve) {
				glBindVertexArray(g.vao);
				glDrawArrays(g.drawMode, min, g.controlPointsPerCurve);
				glBindVertexArray(0);
			}
		}
	}
	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderControlPoints(const std::vector<Geometry>& objects)
{
	glUseProgram(shaderProgramNoTesselation);
	glUniform1f(dxNoTesselationLocation, dx);
	glPointSize(6.0f);
	for (const Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}
	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderDegreeOneCurves(const std::vector<Geometry>& objects)
{
	if (!fontScene) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glUseProgram(shaderProgramNoTesselation);
	glUniform1f(dxNoTesselationLocation, dx);
	for (const Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}
	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderDegreeTwoCurves(const std::vector<Geometry>& objects)
{
	degree = 2;
	if (!fontScene)
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glUseProgram(shaderProgramCurves);
	glUniform1i(degreeLocation, degree);
	glUniform1f(dxCurvesLocation, dx);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	for (const Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}
	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderDegreeThreeCurves(const std::vector<Geometry>& objects)
{
	degree = 3;
	if (!fontScene)
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glUseProgram(shaderProgramCurves);
	glUniform1i(degreeLocation, degree);
	glUniform1f(dxCurvesLocation, dx);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	for (const Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}
	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::assignBuffers(Geometry& geometry) {
	glGenVertexArrays(1, &geometry.vao);
	glBindVertexArray(geometry.vao);
	glGenBuffers(1, &geometry.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &geometry.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void RenderingEngine::setBufferData(Geometry& geometry) {
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.verts.size(), geometry.verts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.colors.size(), geometry.colors.data(), GL_STATIC_DRAW);
}

void RenderingEngine::deleteBufferData(Geometry& geometry) {
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

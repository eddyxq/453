#ifndef RENDERINGENGINE_H_
#define RENDERINGENGINE_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Geometry.h"

class GLFWwindow;

class RenderingEngine {
public:
	RenderingEngine();
	virtual ~RenderingEngine();

	//Renders each object
	void RenderDegreeOneCurves(const std::vector<Geometry>& objects);
	void RenderDegreeTwoCurves(const std::vector<Geometry>& objects);
	void RenderDegreeThreeCurves(const std::vector<Geometry>& objects);

	//Create vao and vbos for objects
	static void assignBuffers(Geometry& geometry);
	static void setBufferData(Geometry& geometry);
	static void deleteBufferData(Geometry& geometry);

	//Ensures that vao and vbos are set up properly
	bool CheckGLErrors();

	//Pointer to the current shader program being used to render
	GLuint shaderProgram;
	GLuint shaderProgram2;
	GLuint d;
	int degree;
	bool fontScene;
};

#endif /* RENDERINGENGINE_H_ */

#ifndef SHADERTOOLS_H_
#define SHADERTOOLS_H_
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ShaderTools {
	std::string LoadSource(const std::string &filename);
	GLuint CompileShader(GLenum shaderType, const std::string &source);
	GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint tcsShader, GLuint tesShader);
	GLuint InitializeShaders();
	GLuint InitializeShaders2();
}

#endif /* SHADERTOOLS_H_ */

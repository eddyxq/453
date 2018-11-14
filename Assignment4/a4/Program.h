#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "imagebuffer.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Light.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;

class Program {
public:
	Program();
	virtual ~Program();

	//Creates the rendering engine and the scene and does the main draw loop
	void start();

	//Initializes GLFW and creates the window
	void setupWindow();

	//Prints system specs to the console
	void QueryGLVersion();

	//New added functions
	void scene1();
	void scene2();
	double getMagnitude(glm::vec3 a);
	double dotProduct(glm::vec3 a, glm::vec3 b);
	glm::vec3 subtractVector(glm::vec3 a, glm::vec3 b);
	glm::vec3 multiplyVector(glm::vec3 a, double b);

	glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b);

	glm::vec3 getRayPlaneIntersection(Ray ray, Plane plane);
	glm::vec3 getRaySphereIntersection(Ray ray, Sphere sphere);
	glm::vec3 getRayTriangleIntersection(Ray ray, Triangle triangle);
	glm::vec3 normalize(Ray ray);

private:
	GLFWwindow* window;
        ImageBuffer image;
};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif /* PROGRAM_H_ */

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
	void init_scene1();
	void init_scene2();
	void init_scene3();

	void displayScene(int scene_number);

	float getMagnitude(glm::vec3 a);

	float getRayPlaneIntersection(Ray ray, Shape plane);
	float getRaySphereIntersection(Ray ray, Shape sphere);
	float getRayTriangleIntersection(Ray ray, Shape triangle);

	float getRayShapeIntersection(Ray ray, Shape shape);

	glm::vec3 applyColor(Ray ray, Shape shape, Light light);


private:
	GLFWwindow* window;
	ImageBuffer image;
};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif /* PROGRAM_H_ */

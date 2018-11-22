#include "Program.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

bool intersectionFound;
int focalLengthAdjustment = 0;

std::vector<Shape> scene1_shapes;
std::vector<Shape> scene2_shapes;
std::vector<Shape> scene3_shapes;

Program::Program() 
{
	setupWindow();
}

Program::~Program() {}

void Program::start() 
{
	int sceneNum;


	std::cout << "Please enter the scene to render (1, 2, or 3): ";
	std::cin >> sceneNum;

	std::cout << "Please enter focal length adjustment, postive number will bring you closer, and negative will push you further: ";
	std::cin >> focalLengthAdjustment;

	//initialize scene objects
	init_scene1();
	init_scene2();
	init_scene3();

	//ray trace the scene
	displayScene(sceneNum);

}

void Program::QueryGLVersion() 
{
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
	std::cout << "OpenGL [ " << version << " ] " << "with GLSL [ " << glslver << " ] " << "on renderer [ " << renderer << " ]" << std::endl;
}

void Program::init_scene1()
{
	//scene1 objects

	//RGB color values
	glm::vec3 grey = glm::vec3(0.8784, 0.8784, 0.8784);
	glm::vec3 lightGrey = glm::vec3(0.6274, 0.6274, 0.6274);
	glm::vec3 cyan = glm::vec3(0.0, 1.0, 1.0);
	glm::vec3 green = glm::vec3(0, 1, 0);
	glm::vec3 red = glm::vec3(1, 0, 0);

	//light
	Light light = Light(glm::vec3(0, 2.5, -7.75));

	//reflective grey sphere
	Shape sphere = Sphere(glm::vec3(0.9, -1.925, -6.69), 0.825);
	sphere.color = lightGrey;
	sphere.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	sphere.ka = glm::vec3(0.5, 0.5, 0.5);
	sphere.km = glm::vec3(0.7f,0.7f,0.7f);
	sphere.p = 10;

	//blue pyramid
	Shape pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -9.55), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(0.11, -2.75, -7.98));
	Shape pyramid2 = Triangle(glm::vec3(0.11, -2.75, -7.98), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.46, -2.75, -7.47));
	Shape pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -7.47), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.97, -2.75, -9.04));
	Shape pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -9.04), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-0.4, -2.75, -9.55));
	pyramid1.color = cyan;
	pyramid1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid1.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid1.km = glm::vec3(0.4f,0.4f,0.4f);
	pyramid1.p = 100;
	pyramid2.color = cyan;
	pyramid2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid2.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid2.km = glm::vec3(0.4f,0.4f,0.4f);
	pyramid2.p = 100;
	pyramid3.color = cyan;
	pyramid3.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid3.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid3.km = glm::vec3(0.4f,0.4f,0.4f);
	pyramid3.p = 100;
	pyramid4.color = cyan;
	pyramid4.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid4.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid4.km = glm::vec3(0.4f,0.4f,0.4f);
	pyramid4.p = 100;

	//ceiling
	Shape ceiling1 = Triangle(glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -5), glm::vec3(-2.75, 2.75, -5));
	Shape ceiling2 = Triangle(glm::vec3(-2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(-2.75, 2.75, -5));
	ceiling1.color = glm::vec3(1.0f, 1.0f, 1.0f);
	ceiling1.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	ceiling1.ka = glm::vec3(1.0, 1.0, 1.0);
	ceiling1.km = glm::vec3(0,0,0);
	ceiling1.p = 1;
	ceiling2.color = glm::vec3(1.0f, 1.0f, 1.0f);
	ceiling2.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	ceiling2.ka = glm::vec3(1.0, 1.0, 1.0);
	ceiling2.km = glm::vec3(0,0,0);
	ceiling2.p = 1;

	//green wall
	Shape green1 = Triangle(glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, -2.75, -10.5));
	Shape green2 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, -2.75, -10.5));
	green1.color = green;
	green1.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	green1.ka = glm::vec3(1.0, 1.0, 1.0);
	green1.km = glm::vec3(0,0,0);
	green1.p = 1;
	green2.color = green;
	green2.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	green2.ka = glm::vec3(0.0, 1.0, 0.0);
	green2.km = glm::vec3(0,0,0);
	green2.p = 1;

	//red wall
	Shape red1 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(-2.75, 2.75, -10.5));
	Shape red2 = Triangle(glm::vec3(-2.75, 2.75, -5), glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, 2.75, -10.5));
	red1.color = red;
	red1.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	red1.ka = glm::vec3(1.0, 1.0, 1.0);
	red1.km = glm::vec3(0,0,0);
	red1.p = 1;
	red2.color = red;
	red2.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	red2.ka = glm::vec3(1.0, 1.0, 1.0);
	red2.km = glm::vec3(0,0,0);
	red2.p = 1;

	//floor
	Shape floor1 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5));
	Shape floor2 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5));
	floor1.color = grey;
	floor1.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	floor1.ka = glm::vec3(1.0, 1.0, 1.0);
	floor1.km = glm::vec3(0,0,0);
	floor1.p = 10;
	floor2.color = grey;
	floor2.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	floor2.ka = glm::vec3(1.0, 1.0, 1.0);
	floor2.km = glm::vec3(0,0,0);
	floor2.p = 10;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -10.5));
	wall.color = grey;
	wall.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	wall.ka = glm::vec3(1.0, 1.0, 1.0);
	wall.km = glm::vec3(0,0,0);
	wall.p = 1;

	scene1_shapes = { wall, red1, red2, green1, green2, floor1, floor2, ceiling1, ceiling2, pyramid1, pyramid4, pyramid3, pyramid2, sphere };
}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit())
	{
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window)
	{
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);
	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);
	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL())
	{
		std::cout << "GLAD init failed" << std::endl;
		return;
	}
	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}

void Program::init_scene2()
{
	//set up scene2 objects

	//RGB color values
	glm::vec3 green = { 0,1,0 };
	glm::vec3 lightGrey = { 0.6274,0.6274,0.6274 };
	glm::vec3 red = { 1,0,0 };
	glm::vec3 yellow = { 0.8,0.8,0 };
	glm::vec3 magenta = { 1,0,1 };
	glm::vec3 grey = { 0.8784,0.8784,0.8784 };
	glm::vec3 cyan = { 0,0.8,0.8 };

	//light
	Light light = Light(glm::vec3(4, 6, -1));

	//floor
	Shape floor = Plane(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0));
	floor.color = lightGrey;
	floor.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	floor.ka = glm::vec3(0.62, 0.62, 0.62);
	floor.km = glm::vec3(0.0f, 0.0f, 0.0f);
	floor.p = 10;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -12));
	wall.color = cyan;
	wall.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	wall.ka = glm::vec3(0.0, 1.0, 1.0);
	wall.km = glm::vec3(0.0f, 0.0f, 0.0f);
	wall.p = 10;

	//large yellow sphere
	Shape yellowSphere = Sphere(glm::vec3(1, -0.5, -3.5), 0.5);
	yellowSphere.color = yellow;
	yellowSphere.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	yellowSphere.ka = glm::vec3(0.1, 0.1, 0.1);
	yellowSphere.km = glm::vec3(0.0f, 0.0f, 0.0f);
	yellowSphere.p = 25;

	//reflective grey sphere
	Shape greySphere = Sphere(glm::vec3(0, 1, -5), 0.4);
	greySphere.color = grey;
	greySphere.ks = glm::vec3(2.5f, 2.5f, 2.5f);
	greySphere.ka = glm::vec3(1.0, 1.0, 1.0);
	greySphere.km = glm::vec3(0.7f, 0.7f, 0.7f);
	greySphere.p = 250;

	//metallic purple sphere
	Shape purpleSphere = Sphere(glm::vec3(-0.8, -0.75, -4), 0.25);
	purpleSphere.color = magenta;
	purpleSphere.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	purpleSphere.ka = glm::vec3(0.9, 0.9, 0.9);
	purpleSphere.km = glm::vec3(0.4f, 0.4f, 0.4f);
	purpleSphere.p = 100;

	//green cone
	Shape cone1 = Triangle(glm::vec3(0, -1, -5.8), glm::vec3(0, 0.6, -5), glm::vec3(0.4, -1, -5.693));
	Shape cone2 = Triangle(glm::vec3(0.4, -1, -5.693), glm::vec3(0, 0.6, -5), glm::vec3(0.6928, -1, -5.4));
	Shape cone3 = Triangle(glm::vec3(0.6928, -1, -5.4), glm::vec3(0, 0.6, -5), glm::vec3(0.8, -1, -5));
	Shape cone4 = Triangle(glm::vec3(0.8, -1, -5), glm::vec3(0, 0.6, -5), glm::vec3(0.6928, -1, -4.6));
	Shape cone5 = Triangle(glm::vec3(0.6928, -1, -4.6), glm::vec3(0, 0.6, -5), glm::vec3(0.4, -1, -4.307));
	Shape cone6 = Triangle(glm::vec3(0.4, -1, -4.307), glm::vec3(0, 0.6, -5), glm::vec3(0, -1, -4.2));
	Shape cone7 = Triangle(glm::vec3(0, -1, -4.2), glm::vec3(0, 0.6, -5), glm::vec3(-0.4, -1, -4.307));
	Shape cone8 = Triangle(glm::vec3(-0.4, -1, -4.307), glm::vec3(0, 0.6, -5), glm::vec3(-0.6928, -1, -4.6));
	Shape cone9 = Triangle(glm::vec3(-0.6928, -1, -4.6), glm::vec3(0, 0.6, -5), glm::vec3(-0.8, -1, -5));
	Shape cone10 = Triangle(glm::vec3(-0.8, -1, -5), glm::vec3(0, 0.6, -5), glm::vec3(-0.6928, -1, -5.4));
	Shape cone11 = Triangle(glm::vec3(-0.6928, -1, -5.4), glm::vec3(0, 0.6, -5), glm::vec3(-0.4, -1, -5.693));
	Shape cone12 = Triangle(glm::vec3(-0.4, -1, -5.693), glm::vec3(0, 0.6, -5), glm::vec3(0, -1, -5.8));
	cone1.color = green;
	cone1.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone1.ka = glm::vec3(0, 0.6, 0);
	cone1.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone1.p = 100;

	cone2.color = green;
	cone2.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone2.ka = glm::vec3(0, 0.6, 0);
	cone2.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone2.p = 100;

	cone3.color = green;
	cone3.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone3.ka = glm::vec3(0, 0.6, 0);
	cone3.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone3.p = 100;

	cone4.color = green;
	cone4.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone4.ka = glm::vec3(0, 0.6, 0);
	cone4.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone4.p = 100;

	cone5.color = green;
	cone5.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone5.ka = glm::vec3(0, 0.6, 0);
	cone5.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone5.p = 100;

	cone6.color = green;
	cone6.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone6.ka = glm::vec3(0, 0.6, 0);
	cone6.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone6.p = 100;

	cone7.color = green;
	cone7.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone7.ka = glm::vec3(0, 0.6, 0);
	cone7.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone7.p = 100;

	cone8.color = green;
	cone8.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone8.ka = glm::vec3(0, 0.6, 0);
	cone8.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone8.p = 100;

	cone9.color = green;
	cone9.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone9.ka = glm::vec3(0, 0.6, 0);
	cone9.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone9.p = 100;

	cone10.color = green;
	cone10.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone10.ka = glm::vec3(0, 0.6, 0);
	cone10.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone10.p = 100;

	cone11.color = green;
	cone11.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone11.ka = glm::vec3(0, 0.6, 0);
	cone11.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone11.p = 100;

	cone12.color = green;
	cone12.ks = glm::vec3(0.8f, 0.8f, 0.8f);
	cone12.ka = glm::vec3(0, 0.6, 0);
	cone12.km = glm::vec3(0.0f, 0.0f, 0.0f);
	cone12.p = 100;

	//shiny red isoahedron 
	Shape isoahedrgon1 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-2.276, -0.4472, -6.149));
	Shape isoahedrgon2 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-2, -1, -7), glm::vec3(-1.276, -0.4472, -7.526));
	Shape isoahedrgon3 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-2.894, -0.4472, -7));
	Shape isoahedrgon4 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.276, -0.4472, -7.851));
	Shape isoahedrgon5 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-1.276, -0.4472, -7.526));
	Shape isoahedrgon6 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-1.106, 0.4472, -7));
	Shape isoahedrgon7 = Triangle(glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.724, 0.4472, -6.149));
	Shape isoahedrgon8 = Triangle(glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-2.724, 0.4472, -6.474));
	Shape isoahedrgon9 = Triangle(glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.724, 0.4472, -7.526));
	Shape isoahedrgon10 = Triangle(glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-1.724, 0.4472, -7.851));
	Shape isoahedrgon11 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.106, 0.4472, -7), glm::vec3(-1.724, 0.4472, -6.149));
	Shape isoahedrgon12 = Triangle(glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-2.724, 0.4472, -6.474));
	Shape isoahedrgon13 = Triangle(glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-2.724, 0.4472, -7.526));
	Shape isoahedrgon14 = Triangle(glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-1.724, 0.4472, -7.851));
	Shape isoahedrgon15 = Triangle(glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-1.106, 0.4472, -7));
	Shape isoahedrgon16 = Triangle(glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-1.106, 0.4472, -7), glm::vec3(-2, 1, -7));
	Shape isoahedrgon17 = Triangle(glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-2, 1, -7));
	Shape isoahedrgon18 = Triangle(glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-2, 1, -7));
	Shape isoahedrgon19 = Triangle(glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-2, 1, -7));
	Shape isoahedrgon20 = Triangle(glm::vec3(-1.106, 0.4472, -7), glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-2, 1, -7));
	isoahedrgon1.color = red;
	isoahedrgon2.color = red;
	isoahedrgon3.color = red;
	isoahedrgon4.color = red;
	isoahedrgon5.color = red;
	isoahedrgon6.color = red;
	isoahedrgon7.color = red;
	isoahedrgon8.color = red;
	isoahedrgon9.color = red;
	isoahedrgon10.color = red;
	isoahedrgon11.color = red;
	isoahedrgon12.color = red;
	isoahedrgon13.color = red;
	isoahedrgon14.color = red;
	isoahedrgon15.color = red;
	isoahedrgon16.color = red;
	isoahedrgon17.color = red;
	isoahedrgon18.color = red;
	isoahedrgon19.color = red;
	isoahedrgon20.color = red;

	isoahedrgon1.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon1.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon1.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon1.p = 100;

	isoahedrgon2.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon2.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon2.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon2.p = 100;

	isoahedrgon3.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon3.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon3.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon3.p = 100;

	isoahedrgon4.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon4.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon4.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon4.p = 100;

	isoahedrgon5.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon5.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon5.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon5.p = 100;

	isoahedrgon6.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon6.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon6.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon6.p = 100;

	isoahedrgon7.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon7.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon7.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon7.p = 100;

	isoahedrgon8.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon8.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon8.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon8.p = 100;

	isoahedrgon9.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon9.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon9.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon9.p = 100;

	isoahedrgon10.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon10.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon10.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon10.p = 100;

	isoahedrgon11.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon11.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon11.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon11.p = 100;

	isoahedrgon12.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon12.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon12.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon12.p = 100;

	isoahedrgon13.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon13.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon13.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon13.p = 100;

	isoahedrgon14.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon14.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon14.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon14.p = 100;

	isoahedrgon15.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon15.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon15.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon15.p = 100;

	isoahedrgon16.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon16.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon16.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon16.p = 100;

	isoahedrgon17.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon17.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon17.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon17.p = 100;

	isoahedrgon18.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon18.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon18.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon18.p = 100;

	isoahedrgon19.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon19.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon19.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon19.p = 100;

	isoahedrgon20.ks = glm::vec3(0.0f, 0.0f, 0.0f);
	isoahedrgon20.ka = glm::vec3(1.0f, 0.0f, 0.0f);
	isoahedrgon20.km = glm::vec3(0.6f, 0.6f, 0.6f);
	isoahedrgon20.p = 100;
	
	scene2_shapes = { wall, floor , isoahedrgon1, isoahedrgon2 , isoahedrgon3 , isoahedrgon4 , isoahedrgon5,
						isoahedrgon6, isoahedrgon7 , isoahedrgon8 , isoahedrgon9 , isoahedrgon10,
						isoahedrgon11, isoahedrgon12 , isoahedrgon13 , isoahedrgon14 , isoahedrgon15,
						isoahedrgon16, isoahedrgon17 , isoahedrgon18 , isoahedrgon19 , isoahedrgon20,
						cone1, cone2, cone3, cone4, cone5, cone6, cone7, cone8, cone9, cone10, cone11,
						cone12, purpleSphere, greySphere, yellowSphere };
}

void Program::init_scene3()
{
	glm::vec3 green = {0,1,0};
	glm::vec3 tree = {1,0.5,0.3138};
	glm::vec3 brown = {0.8471, 0.1647, 0.1647};
	glm::vec3 blue = {0,0,1};
	glm::vec3 sky = { 0,0.5,1 };

	//Light
	Light light = Light(glm::vec3(2, 6, 0));


	//floor
	Shape floor = Plane(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0));
	floor.color = glm::vec3(0.5,1,0);
	floor.ks = glm::vec3(0.0f, 0.52f, 0.0f);
	floor.ka = glm::vec3(0.0, 0.5, 0.0);
	floor.km = glm::vec3(0,0,0);
	floor.p = 10;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -20));
	wall.color = sky;
	wall.ks = glm::vec3(0.0f, 0.2f, 1.0f);
	wall.ka = glm::vec3(0.0, 0.2, 1.0);
	wall.km = glm::vec3(0,0,0);
	wall.p = 10;
	wall.Ia = 1.0f;

	Shape sphere1 = Sphere(glm::vec3(-0.6, 0.8, -4.5), 0.4);
	sphere1.color = green;
	sphere1.ks = glm::vec3(0.0,0.0,0.0);
	sphere1.ka = glm::vec3(0.0, 1.0, 0);
	sphere1.km = glm::vec3(0,0,0);
	sphere1.p = 100;

	Shape sphere2 = Sphere(glm::vec3(-0.6, 0.4, -4.5), 0.4);
	sphere2.color = green;
	sphere2.ks = glm::vec3(0.0,0.0,0.0);
	sphere2.ka = glm::vec3(0.0, 1.0, 0);
	sphere2.km = glm::vec3(0,0,0);
	sphere2.p = 100;

	Shape sphere3 = Sphere(glm::vec3(-1.25, 0.7, -4.5), 0.4);
	sphere3.color = green;
	sphere3.ks = glm::vec3(0.0,0.0,0.0);
	sphere3.ka = glm::vec3(0.0, 1.0, 0);
	sphere3.km = glm::vec3(0,0,0);
	sphere3.p = 100;

	Shape sphere4 = Sphere(glm::vec3(-1.3, 0.4, -4.5), 0.4);
	sphere4.color = green;
	sphere4.ks = glm::vec3(0.0,0.0,0.0);
	sphere4.ka = glm::vec3(0.0, 1.0, 0);
	sphere4.km = glm::vec3(0,0,0);
	sphere4.p = 100;

	Shape sphere5 = Sphere(glm::vec3(-0.9, 0.75, -4.3), 0.4);
	sphere5.color = green;
	sphere5.ks = glm::vec3(0.0,0.0,0.0);
	sphere5.ka = glm::vec3(0.0, 1.0, 0);
	sphere5.km = glm::vec3(0,0,0);
	sphere5.p = 100;

	Shape sphere6 = Sphere(glm::vec3(-0.9, 0.35, -4.3), 0.4);
	sphere6.color = green;
	sphere6.ks = glm::vec3(0.0,0.0,0.0);
	sphere6.ka = glm::vec3(0.0, 1.0, 0);
	sphere6.km = glm::vec3(0,0,0);
	sphere6.p = 100;

	Shape sphere7 = Sphere(glm::vec3(-1.0, 1.1, -4.5), 0.33);
	sphere7.color = green;
	sphere7.ks = glm::vec3(0.0,0.0,0.0);;
	sphere7.ka = glm::vec3(0.0, 1.0, 0);
	sphere7.km = glm::vec3(0,0,0);
	sphere7.p = 100;

	Shape cloud1 = Sphere(glm::vec3(1.8, 2.7, -7.5), 0.5);
	cloud1.color = glm::vec3(1.0,1.0,1.0);
	cloud1.ks = glm::vec3(0.0,0.0,0.0);
	cloud1.ka = glm::vec3(1.0,1.0,1.0);
	cloud1.km = glm::vec3(0,0,0);
	cloud1.p = 100;

	Shape cloud2 = Sphere(glm::vec3(1.8, 2.5, -7.3), 0.4);
	cloud2.color = glm::vec3(1.0,1.0,1.0);
	cloud2.ks = glm::vec3(0.0,0.0,0.0);
	cloud2.ka = glm::vec3(1.0,1.0,1.0);
	cloud2.km = glm::vec3(0,0,0);
	cloud2.p = 100;

	Shape cloud3 = Sphere(glm::vec3(1.7, 2.0, -7.5), 0.5);
	cloud3.color = glm::vec3(1.0,1.0,1.0);
	cloud3.ks = glm::vec3(0.0,0.0,0.0);
	cloud3.ka = glm::vec3(1.0,1.0,1.0);
	cloud3.km = glm::vec3(0,0,0);
	cloud3.p = 100;

	Shape cloud4 = Sphere(glm::vec3(1.0, 2.0, -7.5), 0.5);
	cloud4.color = glm::vec3(1.0,1.0,1.0);
	cloud4.ks = glm::vec3(0.0,0.0,0.0);;
	cloud4.ka = glm::vec3(1.0,1.0,1.0);
	cloud4.km = glm::vec3(0,0,0);
	cloud4.p = 100;

	Shape cloud5 = Sphere(glm::vec3(2.2, 2.0, -7.5), 0.5);
	cloud5.color = glm::vec3(1.0,1.0,1.0);
	cloud5.ks = glm::vec3(0.0,0.0,0.0);
	cloud5.ka = glm::vec3(1.0,1.0,1.0);
	cloud5.km = glm::vec3(0,0,0);
	cloud5.p = 100;

	Shape cloud6 = Sphere(glm::vec3(2.8, 2.15, -7.5), 0.5);
	cloud6.color = glm::vec3(1.0,1.0,1.0);
	cloud6.ks = glm::vec3(0.0,0.0,0.0);
	cloud6.ka = glm::vec3(1.0,1.0,1.0);
	cloud6.km = glm::vec3(0,0,0);
	cloud6.p = 100;

	Shape cloud7 = Sphere(glm::vec3(1.4, 2.5, -7.4), 0.35);
	cloud7.color = glm::vec3(1.0,1.0,1.0);
	cloud7.ks = glm::vec3(0.0,0.0,0.0);
	cloud7.ka = glm::vec3(1.0,1.0,1.0);
	cloud7.km = glm::vec3(0,0,0);
	cloud7.p = 100;

	Shape cloud8 = Sphere(glm::vec3(2.2, 2.5, -7.4), 0.35);
	cloud8.color = glm::vec3(1.0,1.0,1.0);
	cloud8.ks = glm::vec3(0.0,0.0,0.0);
	cloud8.ka = glm::vec3(1.0,1.0,1.0);
	cloud8.km = glm::vec3(0,0,0);
	cloud8.p = 100;

	//Tree pyramid
	Shape pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -5.15), glm::vec3(-0.93, 0.55, -4.51), glm::vec3(0.11, -2.75, -3.58));
	Shape pyramid2 = Triangle(glm::vec3(0.11, -2.75, -3.58), glm::vec3(-0.93, 0.55, -4.51), glm::vec3(-1.46, -2.75, -3.07));
	Shape pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -3.07), glm::vec3(-0.93, 0.55, -4.51), glm::vec3(-1.97, -2.75, -4.64));
	Shape pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -4.64), glm::vec3(-0.93, 0.55, -4.51), glm::vec3(-0.4, -2.75, -5.15));
	pyramid1.color = tree;
	pyramid1.ks = tree;
	pyramid1.ka = tree;
	pyramid1.km = glm::vec3(0,0,0);
	pyramid1.p = 1000;
	pyramid2.color = tree;
	pyramid2.ks = tree;
	pyramid2.ka = tree;
	pyramid1.km = glm::vec3(0,0,0);
	pyramid2.p = 1000;
	pyramid3.color = tree;
	pyramid3.ks = tree;
	pyramid3.ka = tree;
	pyramid1.km = glm::vec3(0,0,0);
	pyramid3.p = 1000;
	pyramid4.color = tree;
	pyramid4.ks = tree;
	pyramid4.ka = tree;
	pyramid1.km = glm::vec3(0,0,0);
	pyramid4.p = 1000;


	//brown cone
	Shape cone1 = Triangle(glm::vec3(1.0, -1, -4.8), glm::vec3(1.0, 0.6, -4), glm::vec3(1.2, -1, -4.693));
	Shape cone2 = Triangle(glm::vec3(1.2, -1, -4.693), glm::vec3(1.0, 0.6, -4), glm::vec3(1.4928, -1, -4.4));
	Shape cone3 = Triangle(glm::vec3(1.4928, -1, -4.4), glm::vec3(1.0, 0.6, -4), glm::vec3(1.6, -1, -4));
	Shape cone4 = Triangle(glm::vec3(1.6, -1, -4), glm::vec3(1.0, 0.6, -4), glm::vec3(1.4928, -1, -3.6));
	Shape cone5 = Triangle(glm::vec3(1.4928, -1, -3.6), glm::vec3(1.0, 0.6, -4), glm::vec3(1.2, -1, -3.307));
	Shape cone6 = Triangle(glm::vec3(0.707, -1, -5.6), glm::vec3(1.0, 0.6, -4), glm::vec3(0.6, -1, -4));
	Shape cone7 = Triangle(glm::vec3(0.6, -1, -4), glm::vec3(1.0, 0.6, -4), glm::vec3(0.707, -1, -4.4));
	Shape cone8 = Triangle(glm::vec3(0.7, -1, -4.4), glm::vec3(1.0, 0.6, -4), glm::vec3(0.8, -1, -4.693));
	Shape cone9 = Triangle(glm::vec3(0.8, -1, -4.693), glm::vec3(1.0, 0.6, -4), glm::vec3(1.3, -1, -4.8));

	cone1.color = brown;
	cone1.ks = glm::vec3(1,1,1);
	cone1.ka = brown;
	cone1.km = glm::vec3(0,0,0);
	cone1.p = 100;

	cone2.color = brown;
	cone2.ks = glm::vec3(1,1,1);
	cone2.ka = brown;;
	cone2.km = glm::vec3(0,0,0);
	cone2.p = 100;
	
	cone3.color = brown;
	cone3.ks = glm::vec3(1,1,1);
	cone3.ka = brown;
	cone3.km = glm::vec3(0,0,0);
	cone3.p = 100;

	cone4.color = brown;
	cone4.ks = glm::vec3(1,1,1);
	cone4.ka = brown;
	cone4.km = glm::vec3(0,0,0);
	cone4.p = 100;

	cone5.color = brown;
	cone5.ks = glm::vec3(1,1,1);
	cone5.ka = brown;
	cone5.km = glm::vec3(0,0,0);
	cone5.p = 100;

	cone6.color = brown;
	cone6.ks = glm::vec3(1,1,1);
	cone6.ka = brown;
	cone6.km = glm::vec3(0,0,0);
	cone6.p = 100;

	cone7.color = brown;
	cone7.ks = glm::vec3(1,1,1);
	cone7.ka = brown;
	cone7.km = glm::vec3(0,0,0);
	cone7.p = 100;

	cone8.color = brown;
	cone8.ks = glm::vec3(1,1,1);
	cone8.ka = brown;
	cone8.km = glm::vec3(0,0,0);
	cone8.p = 100;

	cone9.color = brown;
	cone9.ks = glm::vec3(1,1,1);
	cone9.ka = brown;
	cone9.km = glm::vec3(0,0,0);
	cone9.p = 100;

	
	scene3_shapes = {	sphere1, sphere2, sphere3, sphere4, sphere5, sphere6, sphere7, floor, wall, cone1, cone2,
						cone3, cone4, cone5, cone6, cone7, cone8, cone9, cloud1, cloud2, cloud3, cloud4,
						cloud5, cloud6, cloud7, cloud8, pyramid1, pyramid4, pyramid3, pyramid2 };
						
}

void Program::displayScene(int scene_number)
{
	Light light = Light(glm::vec3(0,0,0));
	std::vector<Shape> shape_array;

	if (scene_number == 1)
	{
		shape_array = scene1_shapes;
		light = Light(glm::vec3(0.0, 2.5, -7.75));

	}

	else if (scene_number == 2)
	{
		shape_array = scene2_shapes;
		light = Light(glm::vec3(4.0, 6.0, -1.0));
	}

	else if (scene_number == 3)
	{
		shape_array = scene3_shapes;
		light = Light(glm::vec3(7.0, 6.0, 2.5));
	}

	int l = -256;
	int r = 256;
	int t = 256;
	int b = -256;
	int nx = 1024;
	int ny = 1024;

	image.Initialize();
	//ran per pixel
	for (int i = 0; i < image.Width(); i++)
	{
		for (int j = 0; j < image.Height(); j++)
		{
			double lowestTime = INFINITY;
			Shape nearestObject;

			/* from the textbook: ray equation
			ray.direction <- -d w + U u + V v
			ray.origin <- e
			*/

			//set up camera
			double u = l + (r - l)*(i + 0.5) / nx;
			double v = b + (t - b)*(j + 0.5) / ny;
			double d = 443.40500673 + focalLengthAdjustment; //calculated distance based on 60 degrees field of view

			Ray ray = Ray(glm::vec3(0.0, 0.0, -0.25), glm::vec3(u, v, -d)); //shoot a ray
			ray.direction = glm::normalize(ray.direction); //normalize

			double time;
			intersectionFound = false;

			for (Shape s : shape_array)
			{
				time = getRayShapeIntersection(ray, s); 
				if (time < lowestTime && time > 0)
				{
					lowestTime = time;
					nearestObject = s;
				}

			}

			if (intersectionFound)
			{
				glm::vec3 color = applyColor(ray, nearestObject, light, lowestTime, 1, shape_array);
				image.SetPixel(i, j, color);
					
				glm::vec3 intersectionP = ray.origin + multiplyVector(ray.direction, lowestTime);
				glm::vec3 shadowDirection = (light.position - intersectionP);
				Ray sRay = Ray(intersectionP, shadowDirection);

				intersectionFound = false;

				for (Shape s : shape_array)
				{
					double ntime = getRayShapeIntersection(sRay, s);
					if ((ntime > 0.0001) && (ntime < 1.0) && (intersectionFound))
					{
						glm::vec3 shadowCol = applyShadow(ray, nearestObject, light);
						image.SetPixel(i, j, shadowCol);
					}
				}
			}
		
		}
	}
	//Main render loop
	while (!glfwWindowShouldClose(window))
	{
		image.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

glm::vec3 Program::reflectRay(double depth, Ray ray, Light light, glm::vec3 km, std::vector<Shape> shape_array, glm::vec3 normal, glm::vec3 intersectionPoint)
{
	glm::vec3 color;
	
	glm::vec3 r = 2 * dot(ray.direction, normal) *  normal;
	Ray reflectedRay = Ray(intersectionPoint, ray.direction - r);
	reflectedRay.origin += 0.0001f * reflectedRay.direction;
	reflectedRay.direction = glm::normalize(reflectedRay.direction);

	if(depth <= 10)
	{
	
		double lowestTime = INFINITY;
		Shape nearestObject;

		double time;
		intersectionFound = false;

		for (Shape s : shape_array)
		{
			time = getRayShapeIntersection(ray, s);
			if (time < lowestTime && time > 0)
			{
				lowestTime = time;
				nearestObject = s;
			}
		}

		if (intersectionFound)
		{
			color = applyColor2(ray, nearestObject, light, lowestTime, 1);

			glm::vec3 intersectionP = ray.origin + multiplyVector(ray.direction, lowestTime);
			glm::vec3 shadowDirection = (light.position - intersectionP);
			Ray sRay = Ray(intersectionP, shadowDirection);

			intersectionFound = false;

			for (Shape s : shape_array)
			{
				double ntime = getRayShapeIntersection(sRay, s);
					if ((ntime > 0.0005) && (ntime < 1.0) && (intersectionFound))
						{
							glm::vec3 shadowCol = applyShadow(ray, nearestObject, light);
							color = shadowCol;
						}
			}
				//calculation for the normal
				glm::vec3 normal;
					if (nearestObject.shapeID == 1)
					{
						normal = intersectionP - nearestObject.center;
					}
					else if (nearestObject.shapeID == 2)
					{
						normal = nearestObject.normal;
					}
					else if (nearestObject.shapeID == 3)
					{
						glm::vec3 x = nearestObject.p1 - nearestObject.p0; //p1 - p0
						glm::vec3 y = nearestObject.p2 - nearestObject.p0; //p2 - p0
						normal = glm::cross(x, y); //cross product
					}
				normal = glm::normalize(normal);
			return (glm::vec3(1,1,1)-nearestObject.km)*color + nearestObject.km * reflectRay(depth++, reflectedRay, light, nearestObject.km, shape_array, normal, intersectionP);
		}
	}
	return color;
}

double Program::getMagnitude(glm::vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double Program::dotProduct(glm::vec3 a, glm::vec3 b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

glm::vec3 Program::subtractVector(glm::vec3 a, glm::vec3 b)
{
	return { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
}

glm::vec3 Program::multiplyVector(glm::vec3 a, double b)
{
	return glm::vec3(a[0]*b, a[1]*b, a[2]*b);
}

glm::vec3 Program::crossProduct(glm::vec3 a, glm::vec3 b)
{
	glm::vec3 cross = { a[1] * b[2] - a[2] * b[1],
						a[2] * b[0] - a[0] * b[2],
						a[0] * b[1] - a[1] * b[0] };
	return cross;
}

double Program::getRayPlaneIntersection(Ray ray, Shape plane)
{
	/*
	ray-plane intersectionformula: (o + t(d) - p) . n = 0
	re-arrange for t, we get: t = (p - o) . n / (d . n)
	*/
	double t = INFINITY;
	
	double numerator = glm::dot((plane.point - ray.origin), plane.normal);
	double denominator = glm::dot(ray.direction, plane.normal);
	// ((point - origin) . n) / (d . n)
	t = numerator / denominator;
	// check for positive t intersections, sets flags appropriately
	if (t >= 0)
	{
		intersectionFound = true;
	}
	else
	{
		t = INFINITY;
	}
	return t;
}

double Program::getRaySphereIntersection(Ray ray, Shape sphere)
{
	/* 
	ray-sphere intersection formula: (o + t(d) - c) . (o + t(d) - c) - r^2 = 0
	*/
	double t = INFINITY;

	double a, b, c;
	//calculate coefficients
	a = dotProduct(ray.direction, ray.direction);
	b = dotProduct(ray.direction, subtractVector(ray.origin, sphere.center)) * 2;
	c = dotProduct(subtractVector(ray.origin, sphere.center), subtractVector(ray.origin, sphere.center)) - (sphere.radius*sphere.radius);
	//check values under the square root to determine the number of intersections
	double discriminant = b * b - 4 * a*c;
	//when positive there is 2 intersections
	if (discriminant > 0.0) 
	{
		intersectionFound = true;
		double t1 = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		double t2 = (-b - sqrt((b*b) - 4 * a*c)) / (2 * a);
		double closerIntersectionPoint = glm::min(t1, t2);
		t = closerIntersectionPoint;
	}
	//when 0 there is 1 intersection
	else if (discriminant == 0)
	{
		intersectionFound = true;
		double closerIntersectionPoint = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		t = closerIntersectionPoint;
	}
	//when negative there is no intersection
	else
	{
		t = INFINITY;
	}
	return t;
}

double Program::getRayTriangleIntersection(Ray ray, Shape triangle)
{
	glm::vec3 x = subtractVector(triangle.p1, triangle.p0); //p1 - p0
	glm::vec3 y = subtractVector(triangle.p2, triangle.p0); //p2 - p0

	glm::vec3 planeNormal = crossProduct(x, y); //cross product

	double n = glm::length(planeNormal); // ||N||

	glm::vec3 normal = glm::normalize(planeNormal); // n = N / ||N||

	Plane tPlane = Plane(normal, triangle.p0);

	glm::vec3 temp = tPlane.point - ray.origin;
	
	double numerator = glm::dot(temp, tPlane.normal);
	double denominator = glm::dot(ray.direction, tPlane.normal);
	// ((point - origin) . n) / (d . n)
	double t = numerator / denominator;

	glm::vec3 intersectionPoint = ray.origin + multiplyVector(ray.direction, t);

	double area = n / 2.0;

	glm::vec3 a1 = crossProduct(intersectionPoint - triangle.p0, triangle.p2 - triangle.p0);
	glm::vec3 a2 = crossProduct(intersectionPoint - triangle.p0, triangle.p1 - triangle.p0);

	double area1 = getMagnitude(a1)/2.0;
	double area2 = getMagnitude(a2)/2.0;

	double u = area1 / area;
	double v = area2 / area;
	double w = (1.0 - u - v);

	if ((u >= 0.0 && u <= 1.0) && (v >= 0.0 && v <= 1.0) && (w >= 0.0 && w <= 1.0) && (t > 0.0) && ((u + v + w) <= 1.0) && ((u + v + w) >= 0.0))
	{
		if ((std::abs((w * triangle.p0.x + u * triangle.p1.x + v * triangle.p2.x) - intersectionPoint.x) < 0.00001) &&
			(std::abs((w * triangle.p0.y + u * triangle.p1.y + v * triangle.p2.y) - intersectionPoint.y) < 0.00001) &&
			(std::abs((w * triangle.p0.z + u * triangle.p1.z + v * triangle.p2.z) - intersectionPoint.z) < 0.00001))
		{
			intersectionFound = true;
			return t;
		}
		else 
		{ 
			return INFINITY;
		}
	}
	else 
	{
		return INFINITY;
	}
}

double Program::getRayShapeIntersection(Ray ray, Shape shape)
{
	double time = INFINITY;
	if (shape.shapeID == 1)
	{
		time = getRaySphereIntersection(ray, shape);
	}
	else if (shape.shapeID == 2)
	{
		time = getRayPlaneIntersection(ray, shape);
	}
	else if (shape.shapeID == 3)
	{
		time = getRayTriangleIntersection(ray, shape);
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	return time;
}

glm::vec3 Program::applyShadow(Ray ray, Shape shape, Light light)
{
	//Ia = ambient light color
	float Ia = 0.6f;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = shape.ka;
	//shape.ka;

	//ka * Ia
	glm::vec3 ambient_component = ka * Ia;
	
	return ambient_component;
}

glm::vec3 Program::applyColor(Ray ray, Shape shape, Light light, double time, double depth, std::vector<Shape> shape_array)
{
	//I = intensity/color of the light source
	float I = 0.4f;

	//kd = diffuse coefficient (surface color)
	glm::vec3 kd = shape.color;

	//Ia = ambient light color
	float Ia = 0.6f;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = kd;

	//ka * Ia
	glm::vec3 ambient_component = ka * Ia;

	glm::vec3 intersectionPoint = ray.origin + multiplyVector(ray.direction, time);

	//l - light source position - intersection point
	glm::vec3 l = light.position - intersectionPoint;
	l = glm::normalize(l);

	//calculation for the normal
	glm::vec3 normal;
	if (shape.shapeID == 1)
	{
		normal = intersectionPoint - shape.center;
	}
	else if (shape.shapeID == 2)
	{
		normal = shape.normal;
	}
	else if (shape.shapeID == 3)
	{
		glm::vec3 x = shape.p1 - shape.p0; //p1 - p0
		glm::vec3 y = shape.p2 - shape.p0; //p2 - p0

		normal = glm::cross(x, y); //cross product
	
	}
	normal = glm::normalize(normal);

	//get max of 0 and n . l
	float max_diffuse = (dotProduct(normal, l) > 0) ? dotProduct(normal, l) : 0;

	//kd * I * max(0, normal . l))
	glm::vec3 diffuse_component = max_diffuse * I * kd;

	//choosing a specular color
	glm::vec3 ks = shape.ks;

	//choosing a exponent
	double p = shape.p; //p = Phong exponent

	//calculations for v and h
	glm::vec3 v = ray.origin - intersectionPoint;
	v = glm::normalize(v);

	//h = (v+l) / (||v+l||)
	glm::vec3 h = (v + l) / glm::length(v + l);

	//max of 0 and (normal . h)^p
	float max_specular = pow(dotProduct(normal, h), p) > 0 ? pow(dotProduct(normal, h), p) : 0;

	//ks * I * max(0, (normal . h)^p)
	glm::vec3 specular_component = max_specular * ks * I;

	//putting the whole thing together, ambient + diffuse + specular
	glm::vec3 L = ambient_component + diffuse_component + specular_component;

	if(shape.km != glm::vec3(0,0,0))
	{
		L = L *(glm::vec3(1,1,1)-shape.km) + shape.km * reflectRay(1, ray, light, shape.km, shape_array, normal, intersectionPoint);
	}

	return L;
}

glm::vec3 Program::applyColor2(Ray ray, Shape shape, Light light, double time, double depth)
{
	//I = intensity/color of the light source
	float I = 0.4f;

	//kd = diffuse coefficient (surface color)
	glm::vec3 kd = shape.color;

	//Ia = ambient light color
	float Ia = 0.6f;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = kd;

	//ka * Ia
	glm::vec3 ambient_component = ka * Ia;

	glm::vec3 intersectionPoint = ray.origin + multiplyVector(ray.direction, time);

	//l - light source position - intersection point
	glm::vec3 l = light.position - intersectionPoint;
	l = glm::normalize(l);

	//calculation for the normal
	glm::vec3 normal;
	if (shape.shapeID == 1)
	{
		normal = intersectionPoint - shape.center;
	}
	else if (shape.shapeID == 2)
	{
		normal = shape.normal;
	}
	else if (shape.shapeID == 3)
	{
		glm::vec3 x = shape.p1 - shape.p0; //p1 - p0
		glm::vec3 y = shape.p2 - shape.p0; //p2 - p0
		normal = glm::cross(x, y); //cross product
	}
	normal = glm::normalize(normal);

	//get max of 0 and n . l
	float max_diffuse = (dotProduct(normal, l) > 0) ? dotProduct(normal, l) : 0;

	//kd * I * max(0, normal . l))
	glm::vec3 diffuse_component = max_diffuse * I * kd;

	//choosing a specular color
	glm::vec3 ks = shape.ks;

	//choosing a exponent
	double p = shape.p; //p = Phong exponent

	//calculations for v and h
	glm::vec3 v = ray.origin - intersectionPoint;
	v = glm::normalize(v);

	//h = (v+l) / (||v+l||)
	glm::vec3 h = (v + l) / glm::length(v + l);

	//max of 0 and (normal . h)^p
	float max_specular = pow(dotProduct(normal, h), p) > 0 ? pow(dotProduct(normal, h), p) : 0;

	//ks * I * max(0, (normal . h)^p)
	glm::vec3 specular_component = max_specular * ks * I;

	//putting the whole thing together, diffuse + specular
	glm::vec3 L = ambient_component + diffuse_component + specular_component;
	
	return L;
}

void ErrorCallback(int error, const char* description) 
{
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

/*------------------------------------------------------------------*/

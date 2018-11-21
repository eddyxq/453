#include "Program.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

bool intersectionFound;

std::vector<Shape> scene1_shapes;
std::vector<Shape> scene2_shapes;

Program::Program() 
{
	setupWindow();
}

Program::~Program() {}

void Program::start() 
{
	//initialize scene objects
	init_scene1();
	init_scene2();
	init_scene3();

	//ray trace the scene

	Ray testRay = Ray(glm::vec3(0,0,0), glm::vec3(0, 1, -4));
	Triangle testTriangle = Triangle(glm::vec3(2,-1,-3), glm::vec3(-1,3,-5), glm::vec3(-1,-1,-3));

	double testTime = getRayTriangleIntersection(testRay, testTriangle);

	//std::cout << testTime << std::endl;
	displayScene(1);
	//displayScene(2);
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
	glm::vec3 cyan = glm::vec3(0.0, 0.6, 0.6);
	glm::vec3 green = glm::vec3(0, 1, 0);
	glm::vec3 red = glm::vec3(1, 0, 0);

	//light
	Light light = Light(glm::vec3(0, 2.5, -7.75));

	//reflective grey sphere
	Shape sphere = Sphere(glm::vec3(0.9, -1.925, -6.69), 0.825);
	sphere.color = lightGrey;
	sphere.ks = glm::vec3(0.1f, 0.1f, 0.1f);
	sphere.ka = glm::vec3(0.5, 0.5, 0.5);
	sphere.p = 10000;

	//blue pyramid
	Shape pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -9.55), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(0.11, -2.75, -7.98));
	Shape pyramid2 = Triangle(glm::vec3(0.11, -2.75, -7.98), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.46, -2.75, -7.47));
	Shape pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -7.47), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.97, -2.75, -9.04));
	Shape pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -9.04), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-0.4, -2.75, -9.55));
	pyramid1.color = cyan;
	pyramid1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid1.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid1.p = 100;
	pyramid2.color = cyan;
	pyramid2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid2.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid2.p = 100;
	pyramid3.color = cyan;
	pyramid3.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid3.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid3.p = 100;
	pyramid4.color = cyan;
	pyramid4.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	pyramid4.ka = glm::vec3(0.0, 1.0, 1.0);
	pyramid4.p = 100;

	//ceiling
	Shape ceiling1 = Triangle(glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -5), glm::vec3(-2.75, 2.75, -5));
	Shape ceiling2 = Triangle(glm::vec3(-2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(-2.75, 2.75, -5));
	ceiling1.color = grey;
	ceiling1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	ceiling1.ka = glm::vec3(0.5, 0.5, 0.5);
	ceiling1.p = 10;
	ceiling2.color = grey;
	ceiling2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	ceiling2.ka = glm::vec3(0.5, 0.5, 0.5);
	ceiling2.p = 10;

	//green wall
	Shape green1 = Triangle(glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, -2.75, -10.5));
	Shape green2 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, -2.75, -10.5));
	green1.color = green;
	green1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	green1.ka = glm::vec3(0.0, 1.0, 0.0);
	green1.p = 10;
	green2.color = green;
	green2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	green2.ka = glm::vec3(0.0, 1.0, 0.0);
	green2.p = 10;

	//red wall
	Shape red1 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(-2.75, 2.75, -10.5));
	Shape red2 = Triangle(glm::vec3(-2.75, 2.75, -5), glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, 2.75, -10.5));
	red1.color = red;
	red1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	red1.ka = glm::vec3(1.0, 0.0, 0.0);
	red1.p = 10;
	red2.color = red;
	red2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	red2.ka = glm::vec3(1.0, 0.0, 0.0);
	red2.p = 10;

	//floor
	Shape floor1 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5));
	Shape floor2 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5));
	floor1.color = grey;
	floor1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	floor1.ka = glm::vec3(1.0, 1.0, 1.0);
	floor1.p = 10;
	floor2.color = grey;
	floor2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	floor2.ka = glm::vec3(1.0, 1.0, 1.0);
	floor2.p = 10;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -10.5));
	wall.color = grey;
	wall.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	wall.ka = glm::vec3(1.0, 1.0, 1.0);
	wall.p = 10;

	scene1_shapes = { wall, red1, red2, green1, green2, floor1, floor2, ceiling1, ceiling2, pyramid1, pyramid4, pyramid3, pyramid2, sphere };
	//scene1_shapes = {sphere};
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
	glm::vec3 yellow = { 1,1,0 };
	glm::vec3 magenta = { 1,0,1 };
	glm::vec3 grey = { 0.8784,0.8784,0.8784 };
	glm::vec3 cyan = { 0,1,1 };

	//light
	Light light = Light(glm::vec3(4, 6, -1));

	//floor
	Shape floor = Plane(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0));
	floor.color = lightGrey;
	floor.ks = glm::vec3(0.5f, 0.5f, 0.5f);
	floor.ka = glm::vec3(0.62, 0.62, 0.62);
	floor.p = 10;
	floor.Ia = 0.8f;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -12));
	wall.color = cyan;
	wall.ks = glm::vec3(0.0f, 1.0f, 1.0f);
	wall.ka = glm::vec3(0.0, 1.0, 1.0);
	wall.p = 10;
	wall.Ia = 1.0f;

	//large yellow sphere
	Shape yellowSphere = Sphere(glm::vec3(1, -0.5, -3.5), 0.5);
	yellowSphere.color = yellow;
	yellowSphere.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	yellowSphere.ka = glm::vec3(1.0, 1.0, 0);
	yellowSphere.p = 100;

	//reflective grey sphere
	Shape greySphere = Sphere(glm::vec3(0, 1, -5), 0.4);
	greySphere.color = grey;
	greySphere.ks = glm::vec3(0.6f, 0.6f, 0.6f);
	greySphere.ka = glm::vec3(0.6, 0.6, 0.6);
	greySphere.p = 1000;
	greySphere.Ia = 1.0f;

	//metallic purple sphere
	Shape purpleSphere = Sphere(glm::vec3(-0.8, -0.75, -4), 0.25);
	purpleSphere.color = magenta;
	purpleSphere.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	purpleSphere.ka = glm::vec3(1.0, 0, 1.0);
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
	cone1.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone1.ka = glm::vec3(0, 1.0, 0);
	cone1.p = 100;

	cone2.color = green;
	cone2.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone2.ka = glm::vec3(0, 1.0, 0);
	cone2.p = 100;

	cone3.color = green;
	cone3.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone3.ka = glm::vec3(0, 1.0, 0);
	cone3.p = 100;

	cone4.color = green;
	cone4.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone4.ka = glm::vec3(0, 1.0, 0);
	cone4.p = 100;

	cone5.color = green;
	cone5.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone5.ka = glm::vec3(0, 1.0, 0);
	cone5.p = 100;

	cone6.color = green;
	cone6.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone6.ka = glm::vec3(0, 1.0, 0);
	cone6.p = 100;

	cone7.color = green;
	cone7.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone7.ka = glm::vec3(0, 1.0, 0);
	cone7.p = 100;

	cone8.color = green;
	cone8.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone8.ka = glm::vec3(0, 1.0, 0);
	cone8.p = 100;

	cone9.color = green;
	cone9.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone9.ka = glm::vec3(0, 1.0, 0);
	cone9.p = 100;

	cone10.color = green;
	cone10.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone10.ka = glm::vec3(0, 1.0, 0);
	cone10.p = 100;

	cone11.color = green;
	cone11.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone11.ka = glm::vec3(0, 1.0, 0);
	cone11.p = 100;

	cone12.color = green;
	cone12.ks = glm::vec3(1.0f, 1.0f, 1.0f);
	cone12.ka = glm::vec3(0.0, 1.0, 0.0);
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
	
	scene2_shapes = { wall, floor , isoahedrgon1, isoahedrgon2 , isoahedrgon3 , isoahedrgon4 , isoahedrgon5,
						isoahedrgon6, isoahedrgon7 , isoahedrgon8 , isoahedrgon9 , isoahedrgon10,
						isoahedrgon11, isoahedrgon12 , isoahedrgon13 , isoahedrgon14 , isoahedrgon15,
						isoahedrgon16, isoahedrgon17 , isoahedrgon18 , isoahedrgon19 , isoahedrgon20,
						cone1, cone2, cone3, cone4, cone5, cone6, cone7, cone8, cone9, cone10, cone11,
						cone12, purpleSphere, greySphere, yellowSphere };
						
	//scene2_shapes = { purpleSphere, greySphere, yellowSphere };
}

void Program::init_scene3()
{
	//work in progress
	//part V scene goes here
}

void Program::displayScene(int scene_number)
{
	Light light = Light(glm::vec3(0,0,0));
	std::vector<Shape> shape_array;

	//std::vector<Shape> plane_array;

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
			double lowestTime = 99999;
			Shape nearestObject;


			/* from the textbook: ray equation
			ray.direction <- -d w + U u + V v
			ray.origin <- e
			*/

			//set up camera
			double u = l + (r - l)*(i + 0.5) / nx;
			double v = b + (t - b)*(j + 0.5) / ny;
			double d = 443.40500673; //calculated distance based on 60 degrees field of view

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
				glm::vec3 color = applyColor(ray, nearestObject, light, lowestTime);
				image.SetPixel(i, j, color);
					
				glm::vec3 intersectionP = ray.origin + multiplyVector(ray.direction, lowestTime);
				glm::vec3 sDir = (light.position - intersectionP);
				//sDir = glm::normalize(sDir);
				Ray sRay = Ray(intersectionP, sDir); 

				intersectionFound = false;

				for (Shape s : shape_array)
				{
					//s.color *= reflectRay(0, ray, light, shape_array);
					double ntime = getRayShapeIntersection(sRay, s);
					if ((ntime > 0.0005) && (ntime < 1.0) && (intersectionFound))
					{
						//std::cout << ntime << std::endl;
						//glm::vec3 ks = s.ks;
						//glm::vec3 kd = s.color;
						
						//s.ks = glm::vec3(0.0, 0.0, 0.0);
						//s.color = glm::vec3(0.0,0.0,0.0);

						glm::vec3 shadowCol = applyShadow(ray, nearestObject, light);
						//applyShadow(ray, s, light);
						//glm::vec3(0,0,0);
						// applyColor(ray, s, light);
						image.SetPixel(i, j, shadowCol);

						//s.ks = ks;
						//s.color = kd;
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

glm::vec3 Program::reflectRay(double depth, Ray rayIn, Light lightIn, std::vector<Shape> shape_arrayIn)
{
	Light light = lightIn;
	std::vector<Shape> shape_array = shape_arrayIn;
	double rColor;

	if (depth <= 1)
	{
		//ran per pixel
		for (int i = 0; i < image.Width(); i++)
		{
			for (int j = 0; j < image.Height(); j++)
			{
				double lowestTime = 99999;
				Shape nearestObject;

				Ray ray = rayIn; //shoot a ray
				ray.direction = glm::normalize(ray.direction); //normalize

				//Ray rayR = ray.direction - 2(dotProduct(ray.direction, normal)*normal;

				for (Shape s : shape_array)
				{
					intersectionFound = false;
					double time = getRayShapeIntersection(ray, s); 
					
					if (time < lowestTime)
					{
						lowestTime = time;
						nearestObject = s;
					}

					if (intersectionFound)
					{
						glm::vec3 rColor;// = applyColor(ray, nearestObject, light); //changed parameter
						//image.SetPixel(i, j, rColor);
					
						glm::vec3 intersectionP = ray.origin + multiplyVector(ray.direction, time);
						glm::vec3 sDir = (light.position - intersectionP);
						Ray sRay = Ray(intersectionP, sDir); 

						intersectionFound = false;

						for (Shape s : shape_array)
						{
							double ntime = getRayShapeIntersection(sRay, s);
							if ((ntime > 0.0005) && (ntime < 1.0) && (intersectionFound))
							{
								rColor *= 0;
								//image.SetPixel(i, j, s.color);
							}
							intersectionFound = false;

							rColor *= reflectRay(depth+1, ray, light, shape_array);
						}
					return rColor;
					}
				}
			}
		}	
	}
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
	double t = 99999;

	//double numerator = dotProduct(subtractVector(plane.point, ray.origin), plane.normal); // (point - origin) . n
	//double denominator = dotProduct(ray.direction, plane.normal); // d . n

	double numerator = glm::dot((plane.point - ray.origin), plane.normal);
	double denominator = glm::dot(ray.direction, plane.normal);

	// check for division by 0 error
	if (denominator == 0) 
	{
		//set intersection flags, returns -1 if no intersection
		//intersectionFound = false;
		//planeIntersection = glm::vec3{ 0,0,0 };
		return t;
	}
	// ((point - origin) . n) / (d . n)
	//std::cout << numerator << std::endl;
	//std::cout << denominator << std::endl;
	t = numerator / denominator;
	// check for positive t intersections, sets flags appropriately
	if (t >= 0)
	{

		intersectionFound = true;
		//intersectionPoint = ray.origin + multiplyVector(ray.direction, t);
	}
	else
	{
		//intersectionFound = false;
		//planeIntersection = glm::vec3{ 0,0,0 };
		t = 99999;
	}
	//std::cout << t << std::endl;
	return t;
}

double Program::getRaySphereIntersection(Ray ray, Shape sphere)
{
	/* 
	ray-sphere intersection formula: (o + t(d) - c) . (o + t(d) - c) - r^2 = 0
	*/
	double t = 99999;

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
		//intersectionPoint = ray.origin + multiplyVector(ray.direction, closerIntersectionPoint);
		t = closerIntersectionPoint;
	}
	//when 0 there is 1 intersection
	else if (discriminant == 0)
	{
		intersectionFound = true;
		double closerIntersectionPoint = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		//intersectionPoint = ray.origin + multiplyVector(ray.direction, closerIntersectionPoint);
		t = closerIntersectionPoint;
	}
	//when negative there is no intersection
	else
	{
		//intersectionFound = false;
		//intersectionPoint = glm::vec3{ 0,0,0 };
		t = 99999;
	}
	//std::cout << t << std::endl;
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
			//intersectionPoint = intersectionPoint;
			//std::cout << t << std::endl;
			return t;
		}
		else 
		{ 
			//intersectionFound = false;
			//intersectionPoint = glm::vec3{ 0,0,0 };
			return 99999;
		}
	}
	else 
	{
		//intersectionFound = false;
		//intersectionPoint = glm::vec3{ 0,0,0 };
		return 99999;
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
		std::cout << "error" << std::endl;
	}
	return time;
}

glm::vec3 Program::applyShadow(Ray ray, Shape shape, Light light)
{
	//Ia = ambient light color
	float Ia = 0.8f;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = shape.ka;

	//ka * Ia
	glm::vec3 ambient_component = ka * Ia;
	
	return ambient_component;
}

glm::vec3 Program::applyColor(Ray ray, Shape shape, Light light, double time)
{
	//I = intensity/color of the light source
	float I = 1.0f;

	//kd = diffuse coefficient (surface color)
	glm::vec3 kd = shape.color;

	//Ia = ambient light color
	float Ia = 1.0f;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = shape.ka;

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
	//float max_diffuse = std::max(glm::dot(normal, l), 0);

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
	//L = ka * Ia + kd * I * max(0, dot(normal, l)) + ks * I * max(0, pow(dot(normal, h), p));
	glm::vec3 L = ambient_component + diffuse_component + specular_component;
	//glm::vec3 L = ambient_component;

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

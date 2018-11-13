#include "Program.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Program::Program() 
{
	setupWindow();
}

Program::~Program() {}

void Program::start() 
{
	
	//code example of ray from tutorial
	/*
	Ray myRay = Ray(glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,-1.0,-4.0));
	glm::vec3 result = myRay.evaluate(2.0);

	std::cout << result.x << std::endl;
	std::cout << result.y << std::endl;
	std::cout << result.z << std::endl;
	*/

	//testing calcs on assign 2a 
	Ray ray = Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, -4.0));
	Sphere sphere = Sphere(glm::vec3(0.0, 0.0, -3.0), 1.0);

	glm::vec3 answer2a = getRaySphereIntersection(ray, sphere);

	std::cout << answer2a[0] << std::endl;
	std::cout << answer2a[1] << std::endl;
	std::cout << answer2a[2] << std::endl;

	//--------

	int l = -256;
	int r = 256;
	int t = 256;
	int b = -256;
	int nx = 256 * 256;
	int ny = 256 * 256;

    image.Initialize();
	for (int i = 0; i < image.Width(); i++) 
	{
		for (int j = 0; j < image.Height(); j++) 
		{
			/*
			ray.direction <- -d w + U u + V v
			ray.origin <- e
			*/

			double u = l + (r - 1)*(i + 0.5) / nx;
			double v = b + (t - b)*(j + 0.5) / ny;
			double d = 443.40500673;

			Ray ray = Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(u, v, -d));
			ray.direction = normalize(ray);

			//std::cout << u << std::endl;
			//std::cout << v << std::endl;

			//if intersects, set pixel color
			image.SetPixel(i, j, glm::vec3(1.0, 0.0, 0.0));
		}
	}
	//Main render loop
	while(!glfwWindowShouldClose(window))
	{
	    image.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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



void Program::QueryGLVersion() 
{
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void Program::scene1()
{
	//set up scene objects

	//light
	Light light = Light(glm::vec3(0, 2.5, -7.75));

	//reflective grey sphere
	Sphere sphere = Sphere(glm::vec3(0.9, -1.925, -6.69), 0.825);

	//blue pyramid
	Triangle pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -9.55), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(0.11, -2.75, -7.98));
	Triangle pyramid2 = Triangle(glm::vec3(0.11, -2.75, -7.98), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.46, -2.75, -7.47));
	Triangle pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -7.47), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.97, -2.75, -9.04));
	Triangle pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -9.04), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-0.4, -2.75, -9.55));

	//ceiling
	Triangle ceiling1 = Triangle(glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -5), glm::vec3(-2.75, 2.75, -5));
	Triangle ceiling2 = Triangle(glm::vec3(-2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(-2.75, 2.75, -5));

	//green wall
	Triangle green1 = Triangle(glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, -2.75, -10.5));
	Triangle green2 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, -2.75, -10.5));

	//red wall
	Triangle red1 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(-2.75, 2.75, -10.5));
	Triangle red2 = Triangle(glm::vec3(-2.75, 2.75, -5), glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, 2.75, -10.5));

	//floor
	Triangle floor1 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5));
	Triangle floor2 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5));

	//back wall
	Plane wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -10.5));
}

void Program::scene2()
{
	//set up scene objects

	//light
	Light light = Light(glm::vec3(4, 6, -1));

	//floor
	Plane floor = Plane(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0));

	//back wall
	Plane wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -12));

	//large yellow sphere
	Sphere yellowSphere = Sphere(glm::vec3(1, -0.5, -3.5), 0.5);

	//reflective grey sphere
	Sphere greySphere = Sphere(glm::vec3(0, 1, -5), 0.4);

	//metallic purple sphere
	Sphere purple = Sphere(glm::vec3(-0.8, -0.75, -4), 0.25);

	//green cone
	Triangle cone1 = Triangle(glm::vec3(0, -1, -5.8), glm::vec3(0, 0.6, -5), glm::vec3(0.4, -1, -5.693));
	Triangle cone2 = Triangle(glm::vec3(0.4, -1, -5.693), glm::vec3(0, 0.6, -5), glm::vec3(0.6928, -1, -5.4));
	Triangle cone3 = Triangle(glm::vec3(0.6928, -1, -5.4), glm::vec3(0, 0.6, -5), glm::vec3(0.8, -1, -5));
	Triangle cone4 = Triangle(glm::vec3(0.8, -1, -5), glm::vec3(0, 0.6, -5), glm::vec3(0.6928, -1, -4.6));
	Triangle cone5 = Triangle(glm::vec3(0.6928, -1, -4.6), glm::vec3(0, 0.6, -5), glm::vec3(0.4, -1, -4.307));
	Triangle cone6 = Triangle(glm::vec3(0.4, -1, -4.307), glm::vec3(0, 0.6, -5), glm::vec3(0, -1, -4.2));
	Triangle cone7 = Triangle(glm::vec3(0, -1, -4.2), glm::vec3(0, 0.6, -5), glm::vec3(-0.4, -1, -4.307));
	Triangle cone8 = Triangle(glm::vec3(-0.4, -1, -4.307), glm::vec3(0, 0.6, -5), glm::vec3(-0.6928, -1, -4.6));
	Triangle cone9 = Triangle(glm::vec3(-0.6928, -1, -4.6), glm::vec3(0, 0.6, -5), glm::vec3(-0.8, -1, -5));
	Triangle cone10 = Triangle(glm::vec3(-0.8, -1, -5), glm::vec3(0, 0.6, -5), glm::vec3(-0.6928, -1, -5.4));
	Triangle cone11 = Triangle(glm::vec3(-0.6928, -1, -5.4), glm::vec3(0, 0.6, -5), glm::vec3(-0.4, -1, -5.693));
	Triangle cone12 = Triangle(glm::vec3(-0.4, -1, -5.693), glm::vec3(0, 0.6, -5), glm::vec3(0, -1, -5.8));

	//shiny red isoahedron 
	Triangle isoahedrgon1 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-2.276, -0.4472, -6.149));
	Triangle isoahedrgon2 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-2, -1, -7), glm::vec3(-1.276, -0.4472, -7.526));
	Triangle isoahedrgon3 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-2.894, -0.4472, -7));
	Triangle isoahedrgon4 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.276, -0.4472, -7.851));
	Triangle isoahedrgon5 = Triangle(glm::vec3(-2, -1, -7), glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-1.276, -0.4472, -7.526));
	Triangle isoahedrgon6 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-1.106, 0.4472, -7));
	Triangle isoahedrgon7 = Triangle(glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.724, 0.4472, -6.149));
	Triangle isoahedrgon8 = Triangle(glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-2.724, 0.4472, -6.474));
	Triangle isoahedrgon9 = Triangle(glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.724, 0.4472, -7.526));
	Triangle isoahedrgon10 = Triangle(glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-1.724, 0.4472, -7.851));
	Triangle isoahedrgon11 = Triangle(glm::vec3(-1.276, -0.4472, -6.474), glm::vec3(-1.106, 0.4472, -7), glm::vec3(-1.724, 0.4472, -6.149));
	Triangle isoahedrgon12 = Triangle(glm::vec3(-2.276, -0.4472, -6.149), glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-2.724, 0.4472, -6.474));
	Triangle isoahedrgon13 = Triangle(glm::vec3(-2.894, -0.4472, -7), glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-2.724, 0.4472, -7.526));
	Triangle isoahedrgon14 = Triangle(glm::vec3(-2.276, -0.4472, -7.851), glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-1.724, 0.4472, -7.851));
	Triangle isoahedrgon15 = Triangle(glm::vec3(-1.276, -0.4472, -7.526), glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-1.106, 0.4472, -7));
	Triangle isoahedrgon16 = Triangle(glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-1.106, 0.4472, -7), glm::vec3(-2, 1, -7));
	Triangle isoahedrgon17 = Triangle(glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-1.724, 0.4472, -6.149), glm::vec3(-2, 1, -7));
	Triangle isoahedrgon18 = Triangle(glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-2.724, 0.4472, -6.474), glm::vec3(-2, 1, -7));
	Triangle isoahedrgon19 = Triangle(glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-2.724, 0.4472, -7.526), glm::vec3(-2, 1, -7));
	Triangle isoahedrgon20 = Triangle(glm::vec3(-1.106, 0.4472, -7), glm::vec3(-1.724, 0.4472, -7.851), glm::vec3(-2, 1, -7));
}

double Program::getMagnitude(glm::vec3 a)
{
	return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
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

glm::vec3 Program::getRaySphereIntersection(Ray ray, Sphere sphere)
{
	double a, b, c;

	a = dotProduct(ray.direction, ray.direction);
	b = dotProduct(ray.direction, subtractVector(ray.origin, sphere.center)) * 2;
	c = dotProduct(subtractVector(ray.origin, sphere.center), subtractVector(ray.origin, sphere.center)) - (sphere.radius*sphere.radius);

	double t1 = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
	double t2 = (-b - sqrt((b*b) - 4 * a*c)) / (2 * a);

	double closerIntersectionPoint = min(t1, t2);

	glm::vec3 intersection = multiplyVector(ray.direction, closerIntersectionPoint);

	return intersection;
}

glm::vec3 Program::normalize(Ray ray)
{
	double length = getMagnitude(ray.direction);
	double x = ray.direction[0] / length;
	double y = ray.direction[1] / length;
	double z = ray.direction[2] / length;

	glm::vec3 normal = {x,y,z};

	return normal;
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






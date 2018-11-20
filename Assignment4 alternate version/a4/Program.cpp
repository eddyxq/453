#include "Program.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool sphereIntersectionFound;
bool planeIntersectionFound;
bool triangeIntersectionFound;

std::vector<Shape> scene1_triangles;
std::vector<Shape> scene1_spheres;
std::vector<Shape> scene1_planes;

std::vector<Shape> scene2_triangles;
std::vector<Shape> scene2_spheres;
std::vector<Shape> scene2_planes;

glm::vec3 sphereIntersection;
glm::vec3 planeIntersection;
glm::vec3 triangleIntersection;

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
	glm::vec3 lighterGrey = { 0.5,0.5,0.5 };

	//light
	Light light = Light(glm::vec3(0, 2.5, -7.75));

	//reflective grey sphere
	Shape sphere = Sphere(glm::vec3(0.9, -1.925, -6.69), 0.825);
	sphere.color = lightGrey;

	//blue pyramid
	Shape pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -9.55), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(0.11, -2.75, -7.98));
	Shape pyramid2 = Triangle(glm::vec3(0.11, -2.75, -7.98), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.46, -2.75, -7.47));
	Shape pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -7.47), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.97, -2.75, -9.04));
	Shape pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -9.04), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-0.4, -2.75, -9.55));
	pyramid1.color = cyan;
	pyramid2.color = cyan;
	pyramid3.color = cyan;
	pyramid4.color = cyan;

	//ceiling
	Shape ceiling1 = Triangle(glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -5), glm::vec3(-2.75, 2.75, -5));
	Shape ceiling2 = Triangle(glm::vec3(-2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(-2.75, 2.75, -5));
	ceiling1.color = lightGrey;
	ceiling2.color = lightGrey;

	//green wall
	Shape green1 = Triangle(glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, -2.75, -10.5));
	Shape green2 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, -2.75, -10.5));
	green1.color = green;
	green2.color = green;

	//red wall
	Shape red1 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(-2.75, 2.75, -10.5));
	Shape red2 = Triangle(glm::vec3(-2.75, 2.75, -5), glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, 2.75, -10.5));
	red1.color = red;
	red2.color = red;

	//floor
	Shape floor1 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5));
	Shape floor2 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5));
	floor1.color = { 0.4,0.4,0.4 };;
	floor2.color = { 0.4,0.4,0.4 };;

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -10.5));
	wall.color = lighterGrey;

	scene1_triangles = { red1, red2, green1, green2, floor1, floor2, ceiling1, ceiling2, pyramid1, pyramid4, pyramid3, pyramid2 };
	scene1_spheres = { sphere };
	scene1_planes = { wall };
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
	glm::vec3 lighterGrey = { 0.4,0.4,0.4 };
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

	//back wall
	Shape wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -12));
	wall.color = cyan;

	//large yellow sphere
	Shape yellowSphere = Sphere(glm::vec3(1, -0.5, -3.5), 0.5);
	yellowSphere.color = yellow;

	//reflective grey sphere
	Shape greySphere = Sphere(glm::vec3(0, 1, -5), 0.4);
	greySphere.color = grey;

	//metallic purple sphere
	Shape purpleSphere = Sphere(glm::vec3(-0.8, -0.75, -4), 0.25);
	purpleSphere.color = magenta;

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
	cone2.color = green;
	cone3.color = green;
	cone4.color = green;
	cone5.color = green;
	cone6.color = green;
	cone7.color = green;
	cone8.color = green;
	cone9.color = green;
	cone10.color = green;
	cone11.color = green;
	cone12.color = green;

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

	scene2_triangles = { isoahedrgon1, isoahedrgon2 , isoahedrgon3 , isoahedrgon4 , isoahedrgon5,
						isoahedrgon6, isoahedrgon7 , isoahedrgon8 , isoahedrgon9 , isoahedrgon10,
						isoahedrgon11, isoahedrgon12 , isoahedrgon13 , isoahedrgon14 , isoahedrgon15,
						isoahedrgon16, isoahedrgon17 , isoahedrgon18 , isoahedrgon19 , isoahedrgon20,
						cone1, cone2, cone3, cone4, cone5, cone6, cone7, cone8, cone9, cone10, cone11,
						cone12 };
	scene2_spheres = { purpleSphere, greySphere, yellowSphere };
	scene2_planes = { wall, floor };
}

void Program::init_scene3()
{
	//work in progress
	//part V scene goes here
}

void Program::displayScene(int scene_number)
{
	Light light = Light(glm::vec3(0, 0, 0));
	std::vector<Shape> triangle_array;
	std::vector<Shape> sphere_array;
	std::vector<Shape> plane_array;

	if (scene_number == 1)
	{
		triangle_array = scene1_triangles;
		sphere_array = scene1_spheres;
		plane_array = scene1_planes;
		light = Light(glm::vec3(0, 2.5, -7.75));

	}
	else if (scene_number == 2)
	{
		triangle_array = scene2_triangles;
		sphere_array = scene2_spheres;
		plane_array = scene2_planes;
		light = Light(glm::vec3(4, 6, -1));
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
			/* from the textbook: ray equation
			ray.direction <- -d w + U u + V v
			ray.origin <- e
			*/

			//set up camera
			float u = l + (r - l)*(i + 0.5) / nx;
			float v = b + (t - b)*(j + 0.5) / ny;
			float d = 443.40500673; //calculated distance based on 60 degrees field of view

			Ray ray = Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(u, v, -d)); //shoot a ray
			glm::normalize(ray.direction); //normalize
			//intersect ray and planes

			float lowestSphereTime = INFINITY;
			float lowestPlaneTime = INFINITY;
			float loweestTriangleTime = INFINITY;

			Shape nearestPlane;
			Shape nearestSphere;
			Shape nearestTriangle;

			for (Shape p : plane_array)
			{
				float planeTime = getRayPlaneIntersection(ray, p); //for plane
				if ((planeIntersectionFound) && (planeTime < lowestPlaneTime))
				{
					//glm::vec3 color = applyColor(ray, p, light);
					//image.SetPixel(i, j, color);
					lowestPlaneTime = planeTime;
					nearestPlane = p;
				}
			}
			//intersect ray and triangles
			for (Shape t : triangle_array)
			{
				float triangleTime = getRayTriangleIntersection(ray, t); //for triangle
				if ((triangeIntersectionFound) && (triangleTime < loweestTriangleTime))
				{
					//glm::vec3 color = applyColor(ray, t, light);
					//image.SetPixel(i, j, color);
					loweestTriangleTime = triangleTime;
					nearestTriangle = t;
				}
			}
			//intersect ray and spheres
			for (Shape s : sphere_array)
			{
				float sphereTime = getRaySphereIntersection(ray, s); //for sphere
				if ((sphereIntersectionFound) && (sphereTime < lowestSphereTime))
				{
					//glm::vec3 color = applyColor(ray, s, light);
					//image.SetPixel(i, j, color);
					lowestSphereTime = sphereTime;
					nearestSphere = s;
				}
			}

			float nearestObjectTime;
			Shape nearestObject;

			if ((lowestSphereTime < lowestPlaneTime) && (lowestSphereTime < loweestTriangleTime))
			{
				glm::vec3 color = applyColor(ray, nearestSphere, light);
				image.SetPixel(i, j, color);
				nearestObjectTime = lowestSphereTime;
				nearestObject = nearestSphere;
			}
			else if ((lowestPlaneTime < lowestSphereTime) && (lowestPlaneTime < loweestTriangleTime))
			{
				glm::vec3 color = applyColor(ray, nearestPlane, light);
				image.SetPixel(i, j, color);
				nearestObjectTime = lowestPlaneTime;
				nearestObject = nearestPlane;
			}
			else if ((loweestTriangleTime < lowestPlaneTime) && (loweestTriangleTime < lowestSphereTime))
			{
				glm::vec3 color = applyColor(ray, nearestTriangle, light);
				image.SetPixel(i, j, color);
				nearestObjectTime = loweestTriangleTime;
				nearestObject = nearestTriangle;
			}
			else
			{
				std::cout << "ERROR NOT POSSIBLE TO GET HERE" << std::endl;
			}

			glm::vec3 intersection = ray.direction * nearestObjectTime;
			glm::vec3 shadowRayDirection = (light.position - intersection);
			shadowRayDirection = glm::normalize(shadowRayDirection);
			Ray shadowRay = Ray(intersection, shadowRayDirection);


			bool inShadow = false;

			planeIntersectionFound = false;
			sphereIntersectionFound = false;
			triangeIntersectionFound = false;

			for (Shape p : plane_array)
			{
				float planeTime = getRayPlaneIntersection(shadowRay, p); //for plane
				if ((planeIntersectionFound) && (planeTime > 0.001) && (planeTime <= 1.0))
				{
					inShadow = true;
				}
			}
			//intersect ray and triangles
			for (Shape t : triangle_array)
			{
				float triangleTime = getRayTriangleIntersection(shadowRay, t); //for triangle
				if ((triangeIntersectionFound) && (triangleTime > 0.001) && (triangleTime <= 1.0))
				{
					inShadow = true;

				}
			}
			//intersect ray and spheres
			for (Shape s : sphere_array)
			{
				float sphereTime = getRaySphereIntersection(shadowRay, s); //for sphere
				if ((sphereIntersectionFound) && (sphereTime > 0.001) && (sphereTime <= 1.0))
				{
					inShadow = true;

				}
			}
			if (inShadow)
			{
				glm::vec3 black = { 0,0,0 };
				image.SetPixel(i, j, black);
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

float Program::getMagnitude(glm::vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float Program::getRayPlaneIntersection(Ray ray, Shape plane)
{
	/*
	ray-plane intersectionformula: (o + t(d) - p) . n = 0
	re-arrange for t, we get: t = (p - o) . n / (d . n)
	*/

	float numerator = glm::dot(plane.point - ray.origin, plane.normal); // (point - origin) . n
	float denominator = glm::dot(ray.direction, plane.normal); // d . n
	// check for division by 0 error
	if (denominator == 0)
	{
		//set intersection flags, returns -1 if no intersection
		planeIntersectionFound = false;
		planeIntersection = glm::vec3{ 0,0,0 };
		return INFINITY;
	}
	// ((point - origin) . n) / (d . n)
	float t = numerator / denominator;
	// check for positive t intersections, sets flags appropriately
	if (t >= 0)
	{
		planeIntersectionFound = true;
		planeIntersection = ray.direction * t;
	}
	else
	{
		planeIntersectionFound = false;
		planeIntersection = glm::vec3{ 0,0,0 };
	}
	return t;
}

float Program::getRaySphereIntersection(Ray ray, Shape sphere)
{
	/*
	ray-sphere intersection formula: (o + t(d) - c) . (o + t(d) - c) - r^2 = 0
	*/

	float a, b, c;
	//calculate coefficients
	a = glm::dot(ray.direction, ray.direction);
	b = glm::dot(ray.direction, ray.origin - sphere.center) * 2;
	c = glm::dot(ray.origin - sphere.center, ray.origin - sphere.center) - (sphere.radius * sphere.radius);
	//check values under the square root to determine the number of intersections
	float discriminant = b * b - 4 * a*c;
	//when positive there is 2 intersections
	if (discriminant > 0.0)
	{
		sphereIntersectionFound = true;
		float t1 = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		float t2 = (-b - sqrt((b*b) - 4 * a*c)) / (2 * a);
		float closerIntersectionPoint = glm::min(t1, t2);
		glm::vec3 intersection = ray.direction * closerIntersectionPoint;
		sphereIntersection = intersection;
		return closerIntersectionPoint;
	}
	//when 0 there is 1 intersection
	else if (discriminant == 0)
	{
		sphereIntersectionFound = true;
		float closerIntersectionPoint = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		glm::vec3 intersection = ray.direction * closerIntersectionPoint;
		sphereIntersection = intersection;
		return closerIntersectionPoint;
	}
	//when negative there is no intersection
	else
	{
		sphereIntersectionFound = false;
		sphereIntersection = glm::vec3{ 0,0,0 };
		return INFINITY;
	}
}

float Program::getRayTriangleIntersection(Ray ray, Shape triangle)
{
	glm::vec3 x = triangle.p1 - triangle.p0; 
	glm::vec3 y = triangle.p2 - triangle.p0; 

	glm::vec3 planeNormal = glm::cross(x, y); //cross product

	float n = getMagnitude(planeNormal);// ||N||

	glm::vec3 normal = { planeNormal[0] / n, planeNormal[1] / n, planeNormal[2] / n }; // n = N / ||N||

	Plane tPlane = Plane(normal, triangle.p0);

	float planeTime = getRayPlaneIntersection(ray, tPlane);

	glm::vec3 intersectionP = ray.direction * planeTime;

	float numerator = glm::dot(tPlane.point - ray.origin, tPlane.normal);
	float denominator = glm::dot(ray.direction, tPlane.normal);

	if (denominator == 0)
	{
		triangeIntersectionFound = false;
		planeIntersectionFound = false;
		planeIntersection = glm::vec3{ 0,0,0 };
		return INFINITY;
	}

	float t = numerator / denominator;

	glm::vec3 pT = intersectionP;

	float area = n / 2.0;

	glm::vec3 a1 = glm::cross(pT - triangle.p0, triangle.p2 - triangle.p0);
	glm::vec3 a2 = glm::cross(pT - triangle.p0, triangle.p1 - triangle.p0);

	float area1 = getMagnitude(a1) / 2.0;
	float area2 = getMagnitude(a2) / 2.0;

	float u = area1 / area;
	float v = area2 / area;
	float w = (1.0 - u - v);

	if ((u >= 0.0 && u <= 1.0) && (v >= 0.0 && v <= 1.0) && (w >= 0.0 && w <= 1.0) && (t > 0.0) && ((u + v + w) <= 1.0) && ((u + v + w) >= 0.0))
	{
		if ((std::abs((w * triangle.p0.x + u * triangle.p1.x + v * triangle.p2.x) - pT.x) < 0.00001) &&
			(std::abs((w * triangle.p0.y + u * triangle.p1.y + v * triangle.p2.y) - pT.y) < 0.00001) &&
			(std::abs((w * triangle.p0.z + u * triangle.p1.z + v * triangle.p2.z) - pT.z) < 0.00001))
		{
			triangeIntersectionFound = true;
			triangleIntersection = intersectionP;
			return t;
		}
		else
		{
			triangeIntersectionFound = false;
			triangleIntersection = glm::vec3{ 0,0,0 };
			return -1;
		}
	}
	else
	{
		triangeIntersectionFound = false;
		triangleIntersection = glm::vec3{ 0,0,0 };
		return INFINITY;
	}
}

glm::vec3 Program::applyColor(Ray ray, Shape shape, Light light)
{
	glm::vec3 intersectionPoint;

	//I = intensity/color of the light source
	float I = 1.0f;

	//kd = diffuse coefficient (surface color)
	glm::vec3 kd = shape.color;

	//Ia = ambient light color
	float Ia = I;

	//ka = ambient coefficient (default color)
	glm::vec3 ka = kd;

	//ka * Ia
	glm::vec3 ambient_component = ka * Ia;

	//calculation for the normal
	glm::vec3 normal;
	if (shape.shapeID == 1)
	{
		intersectionPoint = sphereIntersection;
		normal = intersectionPoint - shape.center;
	}
	else if (shape.shapeID == 2)
	{
		intersectionPoint = planeIntersection;
		normal = shape.normal;
	}
	else if (shape.shapeID == 3)
	{
		intersectionPoint = triangleIntersection;
		glm::vec3 x = shape.p1 - shape.p0; //p1 - p0
		glm::vec3 y = shape.p2 - shape.p0; //p2 - p0
		normal = glm::cross(x, y); //cross product
	}
	normal = glm::normalize(normal);

	//l - light source position - intersection point
	glm::vec3 l = light.position - intersectionPoint;
	l = glm::normalize(l);

	//get max of 0 and n . l
	float max_diffuse = (glm::dot(normal, l) > 0) ? glm::dot(normal, l) : 0;

	//kd * I * max(0, normal . l))
	glm::vec3 diffuse_component = max_diffuse * I * kd;

	//choosing a specular color
	glm::vec3 ks = kd;

	//choosing a exponent
	float p = 1000; //p = Phong exponent

	//calculations for v and h
	glm::vec3 v = ray.origin - intersectionPoint;
	v = glm::normalize(v);

	//h = (v+l) / (||v+l||)
	glm::vec3 h = (v + l) / glm::length(v + l);

	//max of 0 and (normal . h)^p
	float max_specular = pow(glm::dot(normal, h), p) > 0 ? pow(glm::dot(normal, h), p) : 0;

	//ks * I * max(0, (normal . h)^p)
	glm::vec3 specular_component = max_specular * ks * I;

	//putting the whole thing together, diffuse + specular
	//L = ka * Ia + kd * I * max(0, dot(normal, l)) + ks * I * max(0, pow(dot(normal, h), p));
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

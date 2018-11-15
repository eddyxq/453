#include "Program.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool sphereIntersectionFound;
bool planeIntersectionFound;
bool triangeIntersectionFound;

Program::Program() 
{
	setupWindow();
}

Program::~Program() {}

void Program::start() 
{
	scene1();
	//scene2();
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
	//scene1 objects

	glm::vec3 grey = glm::vec3(0.8784, 0.8784, 0.8784);
	glm::vec3 lightGrey = glm::vec3(0.6274, 0.6274, 0.6274);
	glm::vec3 cyan = glm::vec3(0.0, 0.6, 0.6);
	glm::vec3 green = glm::vec3(0, 1, 0);
	glm::vec3 red = glm::vec3(1, 0, 0);

	//reflective grey sphere
	Sphere sphere = Sphere(glm::vec3(0.9, -1.925, -6.69), 0.825);
	sphere.color = lightGrey;

	//blue pyramid
	Triangle pyramid1 = Triangle(glm::vec3(-0.4, -2.75, -9.55), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(0.11, -2.75, -7.98));
	Triangle pyramid2 = Triangle(glm::vec3(0.11, -2.75, -7.98), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.46, -2.75, -7.47));
	Triangle pyramid3 = Triangle(glm::vec3(-1.46, -2.75, -7.47), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-1.97, -2.75, -9.04));
	Triangle pyramid4 = Triangle(glm::vec3(-1.97, -2.75, -9.04), glm::vec3(-0.93, 0.55, -8.51), glm::vec3(-0.4, -2.75, -9.55));
	pyramid1.color = cyan;
	pyramid2.color = cyan;
	pyramid3.color = cyan;
	pyramid4.color = cyan;

	//ceiling
	Triangle ceiling1 = Triangle(glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -5), glm::vec3(-2.75, 2.75, -5));
	Triangle ceiling2 = Triangle(glm::vec3(-2.75, 2.75, -10.5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(-2.75, 2.75, -5));
	ceiling1.color = grey;
	ceiling2.color = grey;

	//green wall
	Triangle green1 = Triangle(glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, 2.75, -10.5), glm::vec3(2.75, -2.75, -10.5));
	Triangle green2 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, 2.75, -5), glm::vec3(2.75, -2.75, -10.5));
	green1.color = green;
	green2.color = green;

	//red wall
	Triangle red1 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(-2.75, 2.75, -10.5));
	Triangle red2 = Triangle(glm::vec3(-2.75, 2.75, -5), glm::vec3(-2.75, -2.75, -5), glm::vec3(-2.75, 2.75, -10.5));
	red1.color = red;
	red2.color = red;

	//floor
	Triangle floor1 = Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5));
	Triangle floor2 = Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5));
	floor1.color = grey;
	floor2.color = grey;

	//back wall
	Plane wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -10.5));
	wall.color = grey;

	Triangle triangle_array[12] = { red1, red2, green1, green2, floor1, floor2, ceiling1, ceiling2, pyramid1, pyramid2, pyramid3, pyramid4 };

	//--------

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

			//setting up the camera
			double u = l + (r - l)*(i + 0.5) / nx;
			double v = b + (t - b)*(j + 0.5) / ny;
			double d = 443.40500673; //calculated distance based on 60 degrees field of view
			
			Ray ray = Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(u, v, -d)); //shoot a ray
			glm::normalize(ray.direction); //normalize

			//intersect ray and plane
			double planeTime = getRayPlaneIntersection(ray, wall); 
			if (planeIntersectionFound)
			{
				image.SetPixel(i, j, wall.color);
			}
			//intersect ray and triangle
			for (Triangle t : triangle_array)
			{
				double triangleTime = getRayTriangleIntersection(ray, t); 
				if (triangeIntersectionFound)
				{
					image.SetPixel(i, j, t.color);
				}
			}
			//intersect ray and sphere
			double sphereTime = getRaySphereIntersection(ray, sphere); 
			if (sphereIntersectionFound)
			{
				image.SetPixel(i, j, sphere.color);
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

void Program::scene2()
{
	//set up scene2 objects

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
	Plane floor = Plane(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0));
	floor.color = lightGrey;

	//back wall
	Plane wall = Plane(glm::vec3(0, 0, 1), glm::vec3(0, 0, -12));
	wall.color = cyan;

	//large yellow sphere
	Sphere yellowSphere = Sphere(glm::vec3(1, -0.5, -3.5), 0.5);
	yellowSphere.color = yellow;

	//reflective grey sphere
	Sphere greySphere = Sphere(glm::vec3(0, 1, -5), 0.4);
	greySphere.color = grey;

	//metallic purple sphere
	Sphere purpleSphere = Sphere(glm::vec3(-0.8, -0.75, -4), 0.25);
	purpleSphere.color = magenta;

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
	
	Triangle triangle_array[32] = { isoahedrgon1, isoahedrgon2 , isoahedrgon3 , isoahedrgon4 , isoahedrgon5,
								   isoahedrgon6, isoahedrgon7 , isoahedrgon8 , isoahedrgon9 , isoahedrgon10,
								   isoahedrgon11, isoahedrgon12 , isoahedrgon13 , isoahedrgon14 , isoahedrgon15,
								   isoahedrgon16, isoahedrgon17 , isoahedrgon18 , isoahedrgon19 , isoahedrgon20,
								   cone1, cone2, cone3, cone4, cone5, cone6, cone7, cone8, cone9, cone10, cone11,
								   cone12};
	Sphere sphere_array[3] = { purpleSphere, greySphere, yellowSphere };
	Plane plane_array[2] = { wall, floor };

	//--------

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
			double u = l + (r - l)*(i + 0.5) / nx;
			double v = b + (t - b)*(j + 0.5) / ny;
			double d = 443.40500673; //calculated distance based on 60 degrees field of view

			Ray ray = Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(u, v, -d)); //shoot a ray
			glm::normalize(ray.direction); //normalize

			for (Plane p : plane_array)
			{
				double planeTime = getRayPlaneIntersection(ray, p); //for plane
				if (planeIntersectionFound)
				{
					image.SetPixel(i, j, p.color);
				}
			}

			for (Triangle t : triangle_array)
			{
				double triangleTime = getRayTriangleIntersection(ray, t); //for triangle

				if (triangeIntersectionFound)
				{
					image.SetPixel(i, j, t.color);
				}
			}
			
			for (Sphere s : sphere_array)
			{
				double sphereTime = getRaySphereIntersection(ray, s); //for sphere
				if (sphereIntersectionFound)
				{
					image.SetPixel(i, j, s.color);
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

double Program::getRayPlaneIntersection(Ray ray, Plane plane)
{
	/*
	ray-plane intersectionformula: (o + t(d) - p) . n = 0
	re-arrange for t, we get: t = (p - o) . n / (d . n)
	*/

	double numerator = dotProduct(subtractVector(plane.point, ray.origin), plane.normal); // (point - origin) . n
	double denominator = dotProduct(ray.direction, plane.normal); // d . n
	// check for division by 0 error
	if (denominator == 0) 
	{
		//set intersection flags, returns -1 if no intersection
		triangeIntersectionFound = false;
		planeIntersectionFound = false;
		return -1;
	}
	// ((point - origin) . n) / (d . n)
	double t = numerator / denominator;
	// check for positive t intersections, sets flags appropriately
	if (t >= 0)
	{
		planeIntersectionFound = true;
	}
	else
	{
		triangeIntersectionFound = false;
		planeIntersectionFound = false;
	}
	return t;
}

double Program::getRaySphereIntersection(Ray ray, Sphere sphere)
{
	/* 
	ray-sphere intersection formula: (o + t(d) - c) . (o + t(d) - c) - r^2 = 0
	*/

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
		sphereIntersectionFound = true;
		double t1 = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		double t2 = (-b - sqrt((b*b) - 4 * a*c)) / (2 * a);
		double closerIntersectionPoint = glm::min(t1, t2);
		glm::vec3 intersection = multiplyVector(ray.direction, closerIntersectionPoint);
		return closerIntersectionPoint;
	}
	//when 0 there is 1 intersection
	else if (discriminant == 0)
	{
		sphereIntersectionFound = true;
		double closerIntersectionPoint = (-b + sqrt((b*b) - 4 * a*c)) / (2 * a);
		glm::vec3 intersection = multiplyVector(ray.direction, closerIntersectionPoint);
		return closerIntersectionPoint;
	}
	//when negative there is no intersection
	else
	{
		sphereIntersectionFound = false;
		return -1;
	}
}

double Program::getRayTriangleIntersection(Ray ray, Triangle triangle)
{
	glm::vec3 x = subtractVector(triangle.p1, triangle.p0); //p1 - p0
	glm::vec3 y = subtractVector(triangle.p2, triangle.p0); //p2 - p0

	glm::vec3 planeNormal = crossProduct(x, y); //cross product

	double n = getMagnitude(planeNormal);// ||N||

	glm::vec3 normal = { planeNormal[0] / n, planeNormal[1] / n, planeNormal[2] / n }; // n = N / ||N||

	Plane tPlane = Plane(normal, triangle.p0);

	double planeTime = getRayPlaneIntersection(ray, tPlane);

	glm::vec3 intersectionP = multiplyVector(ray.direction, planeTime);

	double numerator = dotProduct(subtractVector(tPlane.point, ray.origin), tPlane.normal);
	double denominator = dotProduct(ray.direction, tPlane.normal);

	if (denominator == 0)
	{
		triangeIntersectionFound = false;
		planeIntersectionFound = false;
		return -1;
	}

	double t = numerator / denominator;

	glm::vec3 pT = intersectionP;

	double area = n / 2.0;

	glm::vec3 a1 = crossProduct(pT - triangle.p0, triangle.p2 - triangle.p0);
	glm::vec3 a2 = crossProduct(pT - triangle.p0, triangle.p1 - triangle.p0);

	double area1 = getMagnitude(a1)/2.0;
	double area2 = getMagnitude(a2)/2.0;

	double u = area1 / area;
	double v = area2 / area;
	double w = (1.0 - u - v);

	if ((u >= 0.0 && u <= 1.0) && (v >= 0.0 && v <= 1.0) && (w >= 0.0 && w <= 1.0) && (t > 0.0) && ((u + v + w) <= 1.0) && ((u + v + w) >= 0.0))
	{
		if ((std::abs((w * triangle.p0.x + u * triangle.p1.x + v * triangle.p2.x) - pT.x) < 0.00001) &&
			(std::abs((w * triangle.p0.y + u * triangle.p1.y + v * triangle.p2.y) - pT.y) < 0.00001) &&
			(std::abs((w * triangle.p0.z + u * triangle.p1.z + v * triangle.p2.z) - pT.z) < 0.00001))
		{
			triangeIntersectionFound = true;
			return t;
		}
		else 
		{ 
			triangeIntersectionFound = false;
			return -1;
		}
	}
	else 
	{
		triangeIntersectionFound = false;
		return -1;
	}
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






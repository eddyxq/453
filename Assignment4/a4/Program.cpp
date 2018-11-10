#include "Program.h"
#include "Ray.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Program::Program() 
{
        setupWindow();
}

Program::~Program() {}

struct Light
{
	glm::vec3 vec;
};

struct Sphere
{
	glm::vec3 center;
	double radius;
};

struct Plane
{
	glm::vec3 vec1, vec2;
};

struct Triangle
{
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
};

void Program::start() 
{
	//code example of ray from tutorial
	Ray myRay = Ray(glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,-1.0,-4.0));
	glm::vec3 result = myRay.evaluate(2.0);

	std::cout << result.x << std::endl;
	std::cout << result.y << std::endl;
	std::cout << result.z << std::endl;
	//--------

    image.Initialize();
	for (int i = 0; i < image.Width(); i++) 
	{
	  for (int j = 0; j < image.Height(); j++) 
	  {
	    //set pixel colors here

		//trace my rays here

		  // create ray
		  // get intersection

		// pixel color
	    image.SetPixel(i, j, glm::vec3(1.0, 1.0, 0.0));
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
	
	//light
	Light light;
	light.vec = {0, 2.5, -7.75};

	
	//reflective grey sphere
	Sphere sphere;
	sphere.center = {0.9, -1.925, -6.69};
	sphere.radius = 0.825;
	//blue pyramid
	Triangle pyramid_triangle1, pyramid_triangle2, pyramid_triangle3, pyramid_triangle4;
	pyramid_triangle1.vertex1 = {-0.4, -2.75, -9.55};
	pyramid_triangle1.vertex2 = {-0.93, 0.55, -8.51};
	pyramid_triangle1.vertex3 = {0.11, -2.75, -7.98};

	pyramid_triangle2.vertex1 = {0.11, -2.75, -7.98};
	pyramid_triangle2.vertex2 = {-0.93, 0.55, -8.51};
	pyramid_triangle2.vertex3 = {-1.46, -2.75, -7.47};

	pyramid_triangle3.vertex1 = {-1.46, -2.75, -7.47};
	pyramid_triangle3.vertex2 = {-0.93, 0.55, -8.51};
	pyramid_triangle3.vertex3 = {-1.97, -2.75, -9.04};

	pyramid_triangle4.vertex1 = {-1.97, -2.75, -9.04};
	pyramid_triangle4.vertex2 = {-0.93, 0.55, -8.51};
	pyramid_triangle4.vertex3 = {-0.4, -2.75, -9.55};
	//ceiling
	Triangle ceiling_triangle1, ceiling_triangle2;
	ceiling_triangle1.vertex1 = {2.75, 2.75, -10.5};
	ceiling_triangle1.vertex2 = {2.75, 2.75, -5};
	ceiling_triangle1.vertex3 = {-2.75, 2.75, -5};

	ceiling_triangle2.vertex1 = {-2.75, 2.75, -10.5};
	ceiling_triangle2.vertex2 = {2.75, 2.75, -10.5};
	ceiling_triangle2.vertex3 = {-2.75, 2.75, -5};
	//green wall
	Triangle green_wall_triangle1, green_wall_triangle2;
	green_wall_triangle1.vertex1 = {2.75, 2.75, -5};
	green_wall_triangle1.vertex2 = {2.75, 2.75, -10.5};
	green_wall_triangle1.vertex3 = {2.75, -2.75, -10.5};

	green_wall_triangle2.vertex1 = {2.75, -2.75, -5};
	green_wall_triangle2.vertex2 = {2.75, 2.75, -5};
	green_wall_triangle2.vertex3 = {2.75, -2.75, -10.5};
	//red wall
	Triangle red_wall_triangle1, red_wall_triangle2;
	red_wall_triangle1.vertex1 = {-2.75, -2.75, -5};
	red_wall_triangle1.vertex2 = {-2.75, -2.75, -10.5};
	red_wall_triangle1.vertex3 = {-2.75, 2.75, -10.5};

	red_wall_triangle2.vertex1 = {-2.75, 2.75, -5};
	red_wall_triangle2.vertex2 = {-2.75, -2.75, -5};
	red_wall_triangle2.vertex3 = {-2.75, 2.75, -10.5};
	//floor
	Triangle floor_triangle1, floor_triangle2;
	floor_triangle1.vertex1 = {2.75, -2.75, -5};
	floor_triangle1.vertex2 = {2.75, -2.75, -10.5};
	floor_triangle1.vertex3 = {-2.75, -2.75, -10.5};

	floor_triangle2.vertex1 = {-2.75, -2.75, -5};
	floor_triangle2.vertex2 = {2.75, -2.75, -5};
	floor_triangle2.vertex3 = {-2.75, -2.75, -10.5};
	//back wall
	Plane back_wall;
	back_wall.vec1 = {0, 0, 1};
	back_wall.vec2 = {0, 0, -10.5};
	
}

void Program::scene2()
{

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






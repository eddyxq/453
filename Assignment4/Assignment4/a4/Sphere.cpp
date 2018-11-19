#include "Sphere.h"

Sphere::Sphere(glm::vec3 o, double r) 
{
	center = o;
	radius = r;
	shapeID = 1;
}

Sphere::~Sphere(){}

#include "Triangle.h"

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	p1 = a;
	p2 = b;
	p3 = c;
}

Triangle::~Triangle(){}

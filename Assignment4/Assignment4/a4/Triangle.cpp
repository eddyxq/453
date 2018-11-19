#include "Triangle.h"

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	p0 = a;
	p1 = b;
	p2 = c;
	shapeID = 3;
}

Triangle::~Triangle(){}

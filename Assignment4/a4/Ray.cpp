#include "Ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 d)
{
	origin = o;
	direction = d;
}

Ray::~Ray() {}

glm::vec3 Ray::evaluate(float t) 
{
	return origin + (t * direction);
}
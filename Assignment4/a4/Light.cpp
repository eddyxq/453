#include "Light.h"

Light::Light(glm::vec3 p)
{
	position = p;
	intensity = 0.5;
}

Light::~Light(){}

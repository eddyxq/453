#ifndef PLANE_H_
#define PLANE_H_
#include <glm/vec3.hpp>
#include "Shape.h"

class Plane : public Shape
{
	public:
		Plane(glm::vec3 a, glm::vec3 b);
		virtual ~Plane();

		//glm::vec3 normal;
		//glm::vec3 point;
		//glm::vec3 color;
};

#endif /* PLANE_H_ */
#ifndef PLANE_H_
#define PLANE_H_
#include <glm/vec3.hpp>

class Plane
{
	public:
		Plane(glm::vec3 a, glm::vec3 b);
		virtual ~Plane();

		glm::vec3 normal;
		glm::vec3 point;
};

#endif /* PLANE_H_ */
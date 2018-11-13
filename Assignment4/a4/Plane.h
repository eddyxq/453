#ifndef PLANE_H_
#define PLANE_H_
#include <glm/vec3.hpp>

class Plane
{
	public:
		Plane(glm::vec3 a, glm::vec3 b);
		virtual ~Plane();

		glm::vec3 vec1;
		glm::vec3 vec2;
};

#endif /* PLANE_H_ */
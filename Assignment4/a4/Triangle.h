#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include <glm/vec3.hpp>

class Triangle
{
	public:
		Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		virtual ~Triangle();

		glm::vec3 p0;
		glm::vec3 p1;
		glm::vec3 p2;
};

#endif /* TRIANGLE_H_ */
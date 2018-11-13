#ifndef SPHERE_H_
#define SPHERE_H_
#include <glm/vec3.hpp>

class Sphere
{
	public:
		Sphere(glm::vec3 o, double r);
		virtual ~Sphere();

		glm::vec3 center;
		double radius;
};

#endif /* SPHERE_H_ */
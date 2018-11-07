#ifndef RAY_H_
#define RAY_H_
#include <glm/vec3.hpp>

class Ray 
{
	public:
		Ray(glm::vec3 o, glm::vec3 d);
		virtual ~Ray();

		glm::vec3 evaluate(float t);
		glm::vec3 origin;
		glm::vec3 direction;
};

#endif /* RAY_H_ */

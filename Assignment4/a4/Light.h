#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/vec3.hpp>

class Light
{
	public:
		Light(glm::vec3 a);
		virtual ~Light();

		glm::vec3 vec1;
};

#endif /* LIGHT_H_ */
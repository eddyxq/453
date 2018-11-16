#ifndef LIGHT_H_
#define LIGHT_H_
#include <glm/vec3.hpp>

class Light
{
	public:
		Light(glm::vec3 p);
		virtual ~Light();

		glm::vec3 position;
		double intensity;


};

#endif /* LIGHT_H_ */
#pragma once
#include <glm/vec3.hpp>
class Shape
{
	public:
		Shape();
		virtual ~Shape();


		glm::vec3 color;
		int shapeID;
		//tri
		glm::vec3 p0;
		glm::vec3 p1;
		glm::vec3 p2;
		//plane
		glm::vec3 normal;
		glm::vec3 point;
		//sphere
		glm::vec3 center;
		float radius;
};


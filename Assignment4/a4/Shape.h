#pragma once
#include <glm/vec3.hpp>
class Shape
{
public:
	Shape();
	virtual ~Shape();

	int shapeID;

	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 color;

	glm::vec3 normal;
	glm::vec3 point;

	glm::vec3 center;
	double radius;

};


#ifndef CAPSULE3D_H
#define CAPSULE3D_H

#include "glm/vec3.hpp"

class Capsule3D
{
public:
	Capsule3D(glm::vec3 p1, glm::vec3 p2, float radius);
	glm::vec3 point1;
	glm::vec3 point2;
	float radius;
};

#endif

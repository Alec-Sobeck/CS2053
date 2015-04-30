#pragma once

#include <sstream>
#include "math/ray3.h"
#include <glm/glm.hpp>

Ray3::Ray3(glm::vec3 point, glm::vec3 direction) : point(point), direction(direction)
{
}

glm::vec3 Ray3::getPoint() const
{
	return point;
}

glm::vec3 Ray3::getDirection() const
{
	return direction;
}

bool Ray3::intersectsPlane(const Plane3 &plane) const
{
	if (glm::dot(direction, plane.normal) == 0)
	{
		return false;
	}
	double r1 = glm::dot(plane.normal, plane.pointOnPlane - point);
	r1 = r1 / glm::dot(plane.normal, direction);
	return r1 >= 0;
}

#include <glm/glm.hpp>
#include "math/line3.h"


Line3::Line3(glm::vec3 point, glm::vec3 direction) : point(point), direction(direction)
{
}

glm::vec3 Line3::getPoint() const
{
	return point;
}

glm::vec3 Line3::getDirection() const
{
	return direction;
}

bool Line3::intersectsPlane(const Plane3 &plane) const
{
	if (glm::dot(direction, plane.normal) == 0)
	{
		return false;
	}
	return true;
}




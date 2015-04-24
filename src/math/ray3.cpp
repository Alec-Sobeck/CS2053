
#include <sstream>
#include "math/ray3.h"

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
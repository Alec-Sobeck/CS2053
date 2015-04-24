
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

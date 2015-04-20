
#include "math/line3.h"

Line3::Line3(glm::vec3 point, glm::vec3 direction) : direction(direction), point(point)
{
}

glm::vec3 Line3::getPoint()
{
	return point;
}

void Line3::setPoint(glm::vec3 point)
{
	this->point = point;
}

glm::vec3 Line3::getDirection()
{
	return direction;
}

void Line3::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

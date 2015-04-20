
#include <sstream>
#include "math/ray3.h"

Ray3::Ray3(glm::vec3 point, glm::vec3 direction)
{
	this->point = point;
	this->direction = direction;
}

glm::vec3 Ray3::getPoint()
{
	return point;
}

void Ray3::setPoint(glm::vec3 point)
{
	this->point = point;
}

glm::vec3 Ray3::getDirection()
{
	return direction;
}

void Ray3::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}


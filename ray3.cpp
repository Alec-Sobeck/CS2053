
#include <sstream>
#include "ray3.h"

/**
* Constructs a new Ray3 instance, which requires a two glm::vec3.
* @param point
* @param direction
*/
Ray3::Ray3(glm::vec3 point, glm::vec3 direction)
{
	this->point = point;
	this->direction = direction;
}

/**
* Gets a glm::vec3 which is part of this Ray3.
* @return a glm::vec3, which is sure to be contained in this Ray3
*/
glm::vec3 Ray3::getPoint()
{
	return point;
}

/**
* Changes the point of this ray to a new glm::vec3.
* @param point a glm::vec3 which will replace the current glm::vec3 in this Ray3
*/
void Ray3::setPoint(glm::vec3 point)
{
	this->point = point;
}

/**
* Gets the glm::vec3 which represents the direction of this ray.
* @return a glm::vec3 which represents the direction of this ray
*/
glm::vec3 Ray3::getDirection()
{
	return direction;
}

/**
* Sets the direction vector of this ray to the provided glm::vec3.
* @param direction a glm::vec3 which will be the new direction of this Ray3
*/
void Ray3::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

std::string toString()
{
	std::stringstream ss;
	// TODO: broken toString() method
	//ss << "Ray3[Point: " << point << " Direction: " << direction << "]";
	return ss.str();
}
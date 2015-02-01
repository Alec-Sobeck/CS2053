
#include "line3.h"

/**
 * Constructs a new Line3 instance, which requires a two glm::vec3.
 * @param point
 * @param direction
 */
Line3::Line3(glm::vec3 point, glm::vec3 direction) : direction(direction), point(point)
{
}

/**
* Gets a glm::vec3 which is part of this Line3.
* @return a glm::vec3, which is sure to be contained in this Line3
*/
glm::vec3 Line3::getPoint()
{
	return point;
}

/**
* Changes the point of this line to a new glm::vec3.
* @param point a glm::vec3 which will replace the current glm::vec3 in this Line3
*/
void Line3::setPoint(glm::vec3 point)
{
	this->point = point;
}

/**
* Gets the glm::vec3 which represents the direction of this line.
* @return a glm::vec3 which represents the direction of this line
*/
glm::vec3 Line3::getDirection()
{
	return direction;
}

/**
* Sets the direction vector of this line to the provided glm::vec3.
* @param direction a glm::vec3 which will be the new direction of this Line3
*/
void Line3::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

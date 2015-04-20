
#include "math/linesegment3.h"
#include "glm/glm.hpp"

LineSegment3::LineSegment3(glm::vec3 point1, glm::vec3 point2) : point1(point1), point2(point2)
{
}

glm::vec3 LineSegment3::getPoint1()
{
	return point1;
}

glm::vec3 LineSegment3::getPoint2()
{
	return point2;
}

void LineSegment3::setPoint1(glm::vec3 point)
{
	this->point1 = point;
}

void LineSegment3::setPoint2(glm::vec3 point)
{
	this->point2 = point;
}

glm::vec3 LineSegment3::getAsVec3()
{
	return glm::vec3(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
}

int LineSegment3::getDimension()
{
	return 3;
}

double LineSegment3::length()
{
	return glm::length(getAsVec3());
}

glm::vec3 LineSegment3::getMidPoint()
{
	return glm::vec3(static_cast<float>(point1.x + point2.x) / 2, static_cast<float>(point1.y + point2.y) / 2, static_cast<float>(point1.z + point2.z) / 2);
}

glm::vec3 LineSegment3::getDirection()
{
	return getAsVec3();
}

glm::vec3 LineSegment3::getPoint()
{
	return point1;
}


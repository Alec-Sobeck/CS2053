
#include "linesegment.h"
#include "glm/glm.hpp"

LineSegment::LineSegment(glm::vec3 point1, glm::vec3 point2) : point1(point1), point2(point2)
{
}

glm::vec3 LineSegment::getPoint1()
{
	return point1;
}

glm::vec3 LineSegment::getPoint2()
{
	return point2;
}

void LineSegment::setPoint1(glm::vec3 point)
{
	this->point1 = point;
}

void LineSegment::setPoint2(glm::vec3 point)
{
	this->point2 = point;
}

glm::vec3 LineSegment::getAsVec3()
{
	return glm::vec3(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
}

int LineSegment::getDimension()
{
	return 3; 
	// (point2.getDimension() == point1.getDimension()) ? point1.getDimension() : -1;
}

double LineSegment::length()
{
	return glm::length(getAsVec3());
}

bool LineSegment::equals(LineSegment &s)
{
	//TODO test LineSegment.equals()
	//If the provided LineSegment doesn't have the same number of elements, the LineSegments are not equal
	if (getDimension() != s.getDimension())
	{
		return false;
	}
	glm::vec3 thisvec = getAsVec3();
	glm::vec3 svec = s.getAsVec3();
	return thisvec == svec;
}

glm::vec3 LineSegment::getMidPoint()
{
	//TODO test LineSegment.getMidPoint()
	return glm::vec3(static_cast<float>(point1.x + point2.x) / 2, static_cast<float>(point1.y + point2.y) / 2, static_cast<float>(point1.z + point2.z) / 2);
}

std::string LineSegment::toString()
{
	// TODO broken toString()
	return "line segment";
	//return "Line Segment from " + point1.toString() + "->" + point2.toString();
}

glm::vec3 LineSegment::getDirection()
{
	return getAsVec3();
}

glm::vec3 LineSegment::getPoint()
{
	return point1;
}
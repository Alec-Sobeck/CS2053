
#include "gamemath.h"
#include "math/linesegment2.h"

LineSegment2::LineSegment2(glm::vec2 point1, glm::vec2 point2) : point1(point1), point2(point2)
{
}

glm::vec2 LineSegment2::asVec2() const
{
	return glm::vec2(point2.x - point1.x, point2.y - point1.y);
}

double LineSegment2::length()
{
	return glm::length(asVec2());
}

bool LineSegment2::operator=(const LineSegment2 &s) const
{
	return asVec2() == s.asVec2();
}

glm::vec2 LineSegment2::midpoint()
{
	return glm::vec2((point1.x + point2.x) / 2.0f, (point1.y + point2.y) / 2.0f);
}

void LineSegment2::shorten(float length)
{
	extend(-1 * length);
}

void LineSegment2::extend(float length)
{
	//    	@TODO: determine if this code can fail in certain cases. It does seem to extend properly with a positive length, negative length, and even beyond line length
	//    	This code finds the unit vector of the line segment and scales it to the desired length, it then translates
	//    	the end-point of the line segment with the new (x,y) values generated. This changes the value of point2.
	//    	(formula implemented below:)
	//    	C.x = B.x + (B.x - A.x) / lenAB * length;
	//    	C.y = B.y + (B.y - A.y) / lenAB * length;
	float lenAB = glm::length(asVec2());
	float x = point2.x + (point2.x - point1.x) / lenAB * length;
	float y = point2.y + (point2.y - point1.y) / lenAB * length;
	point2 = glm::vec2(x, y);
}

glm::vec2 LineSegment2::pointAlongLine(float length)
{
	float distance = sqrt(square(point2.x - point1.x) + square(point2.y - point1.y));
	float r = length / distance;
	float x = (r * point2.x + ((1 - r) * point1.x));
	float y = (r * point2.y + ((1 - r) * point1.y));
	return glm::vec2(x, y);
}
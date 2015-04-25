
#include <stdexcept>
#include "math/gamemath.h"
#include "intersection.h"
#include "polygonmath.h"

Rectangle2::Rectangle2(std::vector<glm::vec2> points) : points(points)
{
	if (points.size() != 4)
	{
		throw std::invalid_argument("A Rectangle2 must have 4 vertices");
	}
}

Rectangle2::Rectangle2(float x, float y, float width, float height)
	: points(std::vector<glm::vec2>{ glm::vec2(x, y), glm::vec2(x + width, y), glm::vec2(x + width, y + height), glm::vec2(x, y + height) })
{
}
	
float Rectangle2::getWidth() const
{
	return LineSegment2(points[0], points[1]).length();
}

float Rectangle2::getHeight() const
{
	return LineSegment2(points[0], points[3]).length();
}

void Rectangle2::extendHeight(float changeInHeight)
{
	LineSegment2 left(points[0], points[3]);
	LineSegment2 right(points[1], points[2]);

	glm::vec2 pointLine1 = left.pointAlongLine(left.length() + changeInHeight);
	glm::vec2 pointLine2 = right.pointAlongLine(right.length() + changeInHeight);

	points[3] = pointLine1;
	points[2] = pointLine2;
}

void Rectangle2::extendWidth(float changeInWidth)
{
	LineSegment2 top(points[0], points[1]);
	LineSegment2 bottom(points[3], points[2]);

	glm::vec2 pointLine1 = top.pointAlongLine(top.length() + changeInWidth);
	glm::vec2 pointLine2 = bottom.pointAlongLine(bottom.length() + changeInWidth);

	points[1] = pointLine1;
	points[2] = pointLine2;
}


glm::vec2 Rectangle2::centerOfLeftSide() const
{
	return LineSegment2(points[3], points[0]).midpoint();
}

glm::vec2 Rectangle2::centerOfRightSide() const
{
	return LineSegment2(points[1], points[2]).midpoint();
}

glm::vec2 Rectangle2::getCenter() const
{
	LineSegment2 seg(points[0], points[2]);
	LineSegment2 seg1(points[1], points[3]);
	auto center = intersection(seg, seg1);
	return glm::vec2(center->x, center->y);
}

bool Rectangle2::isProbablyRectangle() const
{
	//The line segments are a bit cheaty. The direction of the bottom and left sides are reversed to easily
	//Compare for equality of the sides.
	LineSegment2 top(points[0], points[1]);
	LineSegment2 bottom(points[3], points[2]);
	LineSegment2 left(points[0], points[3]);
	LineSegment2 right(points[1], points[2]);
	//If the vectors that represent the cheaty LineSegments are equal, the there's a chance this could be a rectangle
	if (top.asVec2() == bottom.asVec2() && left.asVec2() == right.asVec2())
	{
		//Check the corners are all 90 degrees and it's a rectangle
		float radian90 = rad(90.0f);
		if (approximatelyEqual(angleOfConnectedLineSegments(points[1], points[0], points[2]), radian90) &&
			approximatelyEqual(angleOfConnectedLineSegments(points[1], points[0], points[2]), radian90) &&
			approximatelyEqual(angleOfConnectedLineSegments(points[1], points[0], points[2]), radian90) &&
			approximatelyEqual(angleOfConnectedLineSegments(points[1], points[0], points[2]), radian90))
		{
			return true;
		}
	}
	return false;
}
	
void Rectangle2::rotateOnRightCenter(float angle)
{
	rotateOnPoint(points, centerOfRightSide(), angle);
}

void Rectangle2::rotateOnLeftCenter(float angle)
{
	rotateOnPoint(points, centerOfLeftSide(), angle);
}


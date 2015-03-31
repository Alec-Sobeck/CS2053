
#include <sstream>
#include "physics/aabb.h"
#include "math/gamemath.h"
#include "math/linesegment3.h"
#include <algorithm>

AABB::AABB(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax)
 : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax)
{
}

/**
 * Constructs a new AABB ("Axis Aligned Bounding Box").
 * @param origin a Vector3 describing the origin (x,y,z position) of the AABB. The center position
 * @param halfSizes a Vector3 describing the half-width/height/depth of the AABB
 */
AABB::AABB(glm::vec3 origin, glm::vec3 halfSizes)
    : xMin(origin.x - halfSizes.x), xMax(origin.x + halfSizes.x), yMin(origin.y - halfSizes.y),
    yMax(origin.y + halfSizes.y), zMin(origin.z - halfSizes.z), zMax(origin.z + halfSizes.z)
{
}

bool AABB::overlaps(AABB &other)
{
    return(xMin < other.xMax && xMax > other.xMin &&
           yMin < other.yMax && yMax > other.yMin &&
           zMin < other.zMax && zMax > other.zMin);
}

bool AABB::overlaps(AABS &a)
{
	float distanceSquared = a.radius * a.radius;

	if (a.x < xMin)
		distanceSquared -= square(a.x - xMin);
	else if (a.x > xMax)
		distanceSquared -= square(a.x - xMax);
	
	if (a.y < yMin)
		distanceSquared -= square(a.y - yMin);
	else if (a.y > yMax)
		distanceSquared -= square(a.y - yMax);
	
	if (a.z < zMin)
		distanceSquared -= square(a.z - zMin);
	else if (a.z > zMax)
		distanceSquared -= square(a.z - zMax);
	
	return distanceSquared > 0;
}
/*
void AABB::moveX(float amount) {
    xMax += amount;
    xMin += amount;
}

void AABB::moveY(float amount) {
    yMax += amount;
    yMin += amount;
}

void AABB::moveZ(float amount) {
    zMax += amount;
    zMin += amount;
}
*/
void AABB::move(glm::vec3 amounts)
{
    xMax += amounts.x;
    xMin += amounts.x;
    yMax += amounts.y;
    yMin += amounts.y;
    zMax += amounts.z;
    zMin += amounts.z;
}

std::string AABB::toString()
{
    std::stringstream ss;
    ss << "x=[" << xMin << "," << xMax << "]; y=[" << yMin << "," << yMax << "]; z=[" << zMin << "," << zMax << "]";
    return ss.str();
}

float AABB::getXMin()
{
    return xMin;
}

float AABB::getXMax()
{
    return xMax;
}

float AABB::getYMin()
{
    return yMin;
}

float AABB::getYMax()
{
    return yMax;
}

float AABB::getZMin()
{
    return zMin;
}

float AABB::getZMax()
{
    return zMax;
}

float AABB::getYCenter()
{
    return (yMin + yMax) / 2;
}

float AABB::getZCenter()
{
    return (zMin + zMax) / 2;
}

float AABB::getXCenter()
{
    return (xMin + xMax) / 2;
}

glm::vec3 AABB::center()
{
	return glm::vec3((xMin + xMax) / 2, (yMin + yMax) / 2, (zMin + zMax) / 2);
}

bool AABB::cheapOverlaps(Capsule3D &other)
{
	glm::vec3 top_topLeft(xMin, yMax, zMin);
	glm::vec3 top_topRight(xMax, yMax, zMin);
	glm::vec3 top_bottomLeft(xMin, yMax, zMax);
	glm::vec3 top_bottomRight(xMax, yMax, zMax);
	glm::vec3 bottom_topLeft(xMin, yMin, zMin);
	glm::vec3 bottom_topRight(xMax, yMin, zMin);
	glm::vec3 bottom_bottomLeft(xMin, yMin, zMax);
	glm::vec3 bottom_bottomRight(xMax, yMin, zMax);

	// Test the difference faces
	// the top
	Polygon3 top(FlexArray<glm::vec3>{ top_topLeft, top_topRight, top_bottomRight, top_bottomLeft});
	Polygon3 bottom(FlexArray<glm::vec3>{ bottom_topLeft, bottom_topRight, bottom_bottomRight, bottom_bottomLeft});
	Polygon3 left(FlexArray<glm::vec3>{ top_topLeft, top_bottomLeft, bottom_bottomLeft, bottom_topLeft});
	Polygon3 right(FlexArray<glm::vec3>{ top_topRight, top_bottomRight, bottom_bottomRight, bottom_topRight});
	Polygon3 back(FlexArray<glm::vec3>{ top_topLeft, top_topRight, bottom_topRight, bottom_topLeft});
	Polygon3 front(FlexArray<glm::vec3>{ top_bottomLeft, top_bottomRight, bottom_bottomRight, bottom_bottomLeft});

	LineSegment3 seg(other.point1, other.point2);

	if (top.does_intersect_line(seg))
	{
		return true;
	}
	if (bottom.does_intersect_line(seg))
	{
		return true;
	}
	if (left.does_intersect_line(seg))
	{
		return true;
	}
	if (right.does_intersect_line(seg))
	{
		return true;
	}
	if (front.does_intersect_line(seg))
	{
		return true;
	}
	if (back.does_intersect_line(seg))
	{
		return true;
	}
	return false;
}

void AABB::moveTo(float x, float y, float z)
{
	float xHalfsize = (xMax - xMin) / 2;
	float yHalfsize = (yMax - yMin) / 2;
	float zHalfsize = (zMax - zMin) / 2;
	xMin = x - xHalfsize;
	xMax = x + xHalfsize;
	yMin = y - yHalfsize;
	yMax = y + yHalfsize;
	zMin = z - zHalfsize;
	zMax = z + zHalfsize;
}

#include "aabb.h"
#include "math/gamemath.h"

AABB::AABB(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax)
 : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax)
{
}

AABB::AABB(glm::vec3 origin, glm::vec3 halfSizes)
    : xMin(origin.x - halfSizes.x), xMax(origin.x + halfSizes.x), yMin(origin.y - halfSizes.y),
    yMax(origin.y + halfSizes.y), zMin(origin.z - halfSizes.z), zMax(origin.z + halfSizes.z)
{
}

void AABB::moveX(float amount)
{
    xMax += amount;
    xMin += amount;
}

void AABB::moveY(float amount)
{
    yMax += amount;
    yMin += amount;
}

void AABB::moveZ(float amount)
{
    zMax += amount;
    zMin += amount;
}

void AABB::move(glm::vec3 amounts)
{
    xMax += amounts.x;
    xMin += amounts.x;
    yMax += amounts.y;
    yMin += amounts.y;
    zMax += amounts.z;
    zMin += amounts.z;
}

float AABB::getYCenter()
{
	return (yMin + yMax) / 2.0f;
}

float AABB::getZCenter()
{
	return (zMin + zMax) / 2.0f;
}

float AABB::getXCenter()
{
	return (xMin + xMax) / 2.0f;
}

glm::vec3 AABB::center()
{
	return glm::vec3((xMin + xMax) / 2.0f, (yMin + yMax) / 2.0f, (zMin + zMax) / 2.0f);
}

void AABB::moveTo(float x, float y, float z)
{
	float xHalfsize = (xMax - xMin) / 2.0f;
	float yHalfsize = (yMax - yMin) / 2.0f;
	float zHalfsize = (zMax - zMin) / 2.0f;
	xMin = x - xHalfsize;
	xMax = x + xHalfsize;
	yMin = y - yHalfsize;
	yMax = y + yHalfsize;
	zMin = z - zHalfsize;
	zMax = z + zHalfsize;
}
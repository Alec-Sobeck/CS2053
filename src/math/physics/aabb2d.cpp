
#include "aabb2d.h"
#include "math/gamemath.h"

AABB2D::AABB2D(float xMin, float yMin, float xMax, float yMax)
	: xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax)
{
}

AABB2D::AABB2D(glm::vec2 origin, glm::vec2 halfSizes)
    : xMin(origin.x - halfSizes.x), xMax(origin.x + halfSizes.x), yMin(origin.y - halfSizes.y), yMax(origin.y + halfSizes.y)
{
}

void AABB2D::moveX(float amount)
{
    xMax += amount;
    xMin += amount;
}

void AABB2D::moveY(float amount)
{
    yMax += amount;
    yMin += amount;
}


void AABB2D::move(glm::vec2 amounts)
{
    xMax += amounts.x;
    xMin += amounts.x;
    yMax += amounts.y;
    yMin += amounts.y;
}

float AABB2D::getYCenter()
{
	return (yMin + yMax) / 2.0f;
}

float AABB2D::getXCenter()
{
	return (xMin + xMax) / 2.0f;
}

glm::vec2 AABB2D::center()
{
	return glm::vec2((xMin + xMax) / 2.0f, (yMin + yMax) / 2.0f);
}

void AABB2D::moveTo(float x, float y)
{
	float xHalfsize = (xMax - xMin) / 2.0f;
	float yHalfsize = (yMax - yMin) / 2.0f;
	xMin = x - xHalfsize;
	xMax = x + xHalfsize;
	yMin = y - yHalfsize;
	yMax = y + yHalfsize;
}
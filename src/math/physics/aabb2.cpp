
#include "aabb2.h"
#include "math/gamemath.h"

AABB2::AABB2(float xMin, float yMin, float xMax, float yMax)
	: xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax)
{
}

AABB2::AABB2(glm::vec2 origin, glm::vec2 halfSizes)
    : xMin(origin.x - halfSizes.x), xMax(origin.x + halfSizes.x), yMin(origin.y - halfSizes.y), yMax(origin.y + halfSizes.y)
{
}

void AABB2::moveX(float amount)
{
    xMax += amount;
    xMin += amount;
}

void AABB2::moveY(float amount)
{
    yMax += amount;
    yMin += amount;
}


void AABB2::move(glm::vec2 amounts)
{
    xMax += amounts.x;
    xMin += amounts.x;
    yMax += amounts.y;
    yMin += amounts.y;
}

float AABB2::getYCenter()
{
	return (yMin + yMax) / 2.0f;
}

float AABB2::getXCenter()
{
	return (xMin + xMax) / 2.0f;
}

glm::vec2 AABB2::center()
{
	return glm::vec2((xMin + xMax) / 2.0f, (yMin + yMax) / 2.0f);
}

void AABB2::moveTo(float x, float y)
{
	float xHalfsize = (xMax - xMin) / 2.0f;
	float yHalfsize = (yMax - yMin) / 2.0f;
	xMin = x - xHalfsize;
	xMax = x + xHalfsize;
	yMin = y - yHalfsize;
	yMax = y + yHalfsize;
}
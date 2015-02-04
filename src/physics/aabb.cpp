
#include <sstream>
#include "physics/aabb.h"

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



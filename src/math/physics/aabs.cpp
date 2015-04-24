

#include "aabs.h"
#include "math/polygon3.h"
#include "math/gamemath.h"

AABS::AABS() : x(0), y(0), z(0), radius(0)
{

}

AABS::AABS(glm::vec3 pos, float radius) : x(pos.x), y(pos.y), z(pos.z), radius(radius)
{

}

AABS::AABS(float x, float y, float z, float radius) : x(x), y(y), z(z), radius(radius)
{
}

float AABS::surfaceArea()
{
    return 4.0f * PI * radius * radius;
}

float AABS::volume()
{
    return 1.33333333333f * PI * radius * radius * radius;
}

void AABS::moveTo(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

#include <cmath>
#include "glm/glm.hpp"
#include "math/gamemath.h"


double toRad(double deg)
{
    return deg / (180.0 / PI_D);
}

float toRad(float deg)
{
    return deg / (180.0f / PI);
}

double toRad(int deg)
{
    return static_cast<double>(deg) / (180.0f / PI_D);
}

double toDeg(double rad)
{
    return rad * (180.0 / PI_D);
}

float toDeg(float rad)
{
    return rad * (180.0f / PI);
}

double toDeg(int rad)
{
    return static_cast<double>(rad) * (180.0 / PI_D);
}

// TODO -- verify this is working as intended
bool approximatelyEqual(float a, float b)
{
    return ((a - b) < 0.00001 && (a - b) > -0.00001) ? true : false;
}

bool parallel(glm::vec3 v1, glm::vec3 v2)
{
	glm::vec3 thisAsUnitVector = glm::normalize(v1);
	glm::vec3 vUnitVector = glm::normalize(v2);
	glm::vec3 vCopy(vUnitVector.x * -1, vUnitVector.y * -1, vUnitVector.z * -1);
	return thisAsUnitVector == vCopy || thisAsUnitVector == vUnitVector;
}

bool perpendicular(glm::vec3 v1, glm::vec3 v2)
{
	return approximatelyEqual(glm::dot(v1, v2), 0);
}

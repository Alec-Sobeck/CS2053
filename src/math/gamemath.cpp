
#include <cmath>
#include <glm/glm.hpp>
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



float round2(float val)
{
    return roundf(val * 100) / 100;
}

glm::mat4x4 createLookAtMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	glm::vec3 F = glm::normalize(target - eye);
	glm::vec3 L = glm::normalize(glm::cross(up, F));
	glm::vec3 U = glm::cross(F, L);
	glm::vec3 T(
		-glm::dot(L, eye), 
		-glm::dot(U, eye),
		-glm::dot(F, eye)
		);
	glm::mat4x4 mat = {
		L.x, U.x, F.x, 0, 
		L.y, U.y, F.y, 0,
		L.z, U.z, F.z, 0,
		T.x, T.y, T.z, 1
	};
	return mat;
}

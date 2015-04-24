
#include <sstream>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "math/gamemath.h"
#include "math/linesegment3.h"
#include "math/line3.h"
#include "math/ray3.h"
#include "math/plane3.h"

Plane3::Plane3(glm::vec3 pointOnPlane, glm::vec3 normal) 
	: normal(normal), pointOnPlane(pointOnPlane)
{
}

Plane3::Plane3(glm::vec3 pointOnPlane, std::vector<glm::vec3> directions) 
	: pointOnPlane(pointOnPlane)
{
	/// @TODO ensure this calculation works properly. Is it right handed coordinate system?
	normal = glm::normalize(glm::cross(directions.at(0), directions.at(1)));
}

Plane3::Plane3(float a, float b, float c, float d)
	: normal(glm::normalize(glm::vec3(a, b, c))), pointOnPlane(glm::vec3(-d * normal.x, -d * normal.y, -d * normal.z))
{
}

Plane3::Plane3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
	: pointOnPlane(point1)
{
	/// @TODO test this calculation works
	glm::vec3 first = point2 - point1;
	glm::vec3 second = point3 - point1;
	if (parallel(first, second))
	{
		throw std::invalid_argument("Co-linear points are not allowed.");
	}
	normal = glm::cross(first, second);
}

bool Plane3::isPerpendicular(glm::vec3 other)
{
	return parallel(normal, other);
}

glm::vec4 Plane3::getGeneralEquation()
{
	return glm::vec4(normal.x, normal.y, normal.z, -(glm::dot(normal, pointOnPlane)));
}

float Plane3::distanceToPoint(glm::vec3 vector)
{
	glm::vec4 planeEquation = getGeneralEquation();

	float result = planeEquation.x * vector.x +
		planeEquation.y * vector.y +
		planeEquation.z * vector.z +
		planeEquation.w;

	result /= glm::length(planeEquation);
	return result;
}


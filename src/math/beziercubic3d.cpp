
#include <stdexcept>
#include "beziercubic3d.h"
#include "interpolators.h"


BezierCubic3D::BezierCubic3D(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
	: point1(a), point2(b), point3(c), point4(d)
{
}

glm::vec3 BezierCubic3D::getPoint(float t)
{
	if (t < 0 || t > 1)
	{
		throw std::invalid_argument("t must be between 0 and 1");
	}
	// First level
	glm::vec3 a1 = linearInterpolate(point1, point2, t);
	glm::vec3 b1 = linearInterpolate(point2, point3, t);
	glm::vec3 c1 = linearInterpolate(point3, point4, t);

	// Second level
	glm::vec3 a2 = linearInterpolate(a1, b1, t);
	glm::vec3 b2 = linearInterpolate(b1, c1, t);

	return linearInterpolate(a2, b2, t);
}

std::vector<glm::vec3> BezierCubic3D::getControlPoints()
{
	return std::vector<glm::vec3>{ point1, point2, point3, point4 };
}

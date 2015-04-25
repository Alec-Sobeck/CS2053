
#include <stdexcept>
#include "bezierquadratic3d.h"
#include "interpolators.h"


BezierQuadratic3D::BezierQuadratic3D(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	point1 = a;
	point2 = b;
	point3 = c;
}

glm::vec3 BezierQuadratic3D::getPoint(float t)
{
	if (t < 0 || t > 1)
	{
		throw std::invalid_argument("t must be between 0 and 1");
	}

	glm::vec3 a = linearInterpolate(point1, point2, t);
	glm::vec3 b = linearInterpolate(point2, point3, t);

	return linearInterpolate(a, b, t);
}

std::vector<glm::vec3> BezierQuadratic3D::getControlPoints()
{
	return std::vector<glm::vec3>{ point1, point2, point3 };
}

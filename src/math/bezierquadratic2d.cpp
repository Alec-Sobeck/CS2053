
#include <stdexcept>
#include "bezierquadratic2d.h"
#include "interpolators.h"


BezierQuadratic2D::BezierQuadratic2D(glm::vec2 a, glm::vec2 b, glm::vec2 c)
	: point1(a), point2(b), point3(c)
{
}

glm::vec2 BezierQuadratic2D::getPoint(float t)
{
	if (t < 0 || t > 1)
	{
		throw std::invalid_argument("t must be between 0 and 1");
	}

	glm::vec2 a = linearInterpolate(point1, point2, t);
	glm::vec2 b = linearInterpolate(point2, point3, t);

	return linearInterpolate(a, b, t);
}

std::vector<glm::vec2> BezierQuadratic2D::getControlPoints()
{
	return std::vector<glm::vec2>{ point1, point2, point3 };
}

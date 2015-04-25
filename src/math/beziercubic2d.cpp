
#include <stdexcept>
#include "beziercubic2d.h"
#include "interpolators.h"

BezierCubic2D::BezierCubic2D(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d)
	: point1(a), point2(b), point3(c), point4(d)
{
}

glm::vec2 BezierCubic2D::getPoint(float t)
{
	if (t < 0 || t > 1)
	{
		throw std::invalid_argument("t must be between 0 and 1");
	}
	// First level
	glm::vec2 a1 = linearInterpolate(point1, point2, t);
	glm::vec2 b1 = linearInterpolate(point2, point3, t);
	glm::vec2 c1 = linearInterpolate(point3, point4, t);

	// Second level
	glm::vec2 a2 = linearInterpolate(a1, b1, t);
	glm::vec2 b2 = linearInterpolate(b1, c1, t);

	return linearInterpolate(a2, b2, t);
}

std::vector<glm::vec2> BezierCubic2D::getControlPoints()
{
	return std::vector<glm::vec2>{point1, point2, point3, point4};
}


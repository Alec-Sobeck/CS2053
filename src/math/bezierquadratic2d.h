#pragma once

#include <vector>
#include <glm/vec2.hpp>

class BezierQuadratic2D
{
private:
	glm::vec2 point1;
	glm::vec2 point2;
	glm::vec2 point3;

public:
	BezierQuadratic2D(glm::vec2 a, glm::vec2 b, glm::vec2 c);
	///
	/// Gets a vec2 t% along the curve
	/// \param t a float from 0 to 1 representing progress along the curve
	/// \return a vec2 representing the point on the curve at progress t.
	///
	glm::vec2 getPoint(float t);
	std::vector<glm::vec2> getControlPoints();
};

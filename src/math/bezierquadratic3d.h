#pragma once

#include <vector>
#include <glm/vec3.hpp>

class BezierQuadratic3D
{
private:
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;

public:
	BezierQuadratic3D(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	///
	/// Gets a Vector3 t% along the curve
	/// \param t a float from 0 to 1 representing progress along the curve
	/// \return A vec2 representing the point on the curve at progress t.
	/// 
	glm::vec3 getPoint(float t);
	std::vector<glm::vec3> getControlPoints();
};


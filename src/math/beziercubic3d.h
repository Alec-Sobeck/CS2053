#pragma once

#include <vector>
#include <glm/vec3.hpp>

class BezierCubic3D
{
private:
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 point4;
public:
	BezierCubic3D(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
	glm::vec3 getPoint(float t);
	std::vector<glm::vec3> getControlPoints();
};


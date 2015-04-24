
#include <glm/glm.hpp>
#include "math/linesegment3.h"

LineSegment3::LineSegment3(glm::vec3 point1, glm::vec3 point2) : point1(point1), point2(point2)
{
}

glm::vec3 LineSegment3::asVec3() const
{
	return glm::vec3(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
}

double LineSegment3::length()
{
	return glm::length(asVec3());
}

bool LineSegment3::operator=(const LineSegment3 &s) const
{
	return asVec3() == s.asVec3();
}

glm::vec3 LineSegment3::midpoint()
{
	return glm::vec3((point1.x + point2.x) / 2.0f, (point1.y + point2.y) / 2.0f, (point1.z + point2.z) / 2.0f);
}

glm::vec3 LineSegment3::getPoint() const
{
	return point1;
}

glm::vec3 LineSegment3::getDirection() const
{
	return asVec3();
}

bool LineSegment3::intersectsPlane(const Plane3 &plane) const
{
	if (glm::dot(getDirection(), plane.normal) == 0)
	{
		return false;
	}
	double r1 = glm::dot(plane.normal, plane.pointOnPlane - getPoint());
	r1 = r1 / glm::dot(plane.normal, getDirection());
	return (r1 >= 0 && r1 <= 1);
}
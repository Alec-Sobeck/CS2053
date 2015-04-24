
#include "math/gamemath.h"
#include "collision.h"
#include "math/linesegment3.h"
#include <algorithm>
#include "math/triangle3.h"

bool intersects(const AABS &first, const AABS &second)
{
	return (square(first.x - second.x) + square(first.y - second.y) + square(first.z - second.z)) < square(first.radius + second.radius);
}

bool intersects(const AABS &first, const AABB &second)
{
	float distanceSquared = first.radius * first.radius;

	if (first.x < second.xMin)
		distanceSquared -= square(first.x - second.xMin);
	else if (first.x > second.xMax)
		distanceSquared -= square(first.x - second.xMax);

	if (first.y < second.yMin)
		distanceSquared -= square(first.y - second.yMin);
	else if (first.y > second.yMax)
		distanceSquared -= square(first.y - second.yMax);

	if (first.z < second.zMin)
		distanceSquared -= square(first.z - second.zMin);
	else if (first.z > second.zMax)
		distanceSquared -= square(first.z - second.zMax);

	return distanceSquared > 0;
}

bool intersectsTriangle(const AABS &first, const Triangle3 &triangle)
{
	// If the sphere is further away from the plane than its radius, it can not collide, fail-fast.
	if (triangle.getPlane().distanceToPoint(glm::vec3(first.x, first.y, first.z)) >= first.radius)
	{
		return false;
	}

	// Begin vertex checks
	glm::vec3 a = triangle.point1;
	glm::vec3 b = triangle.point2;
	glm::vec3 c = triangle.point3;

	float aa = glm::dot(a, a);
	float ab = glm::dot(a, b);
	float ac = glm::dot(a, c);
	float bb = glm::dot(b, b);
	float bc = glm::dot(b, c);
	float cc = glm::dot(c, c);
	float rr = first.radius * first.radius;

	bool sep1 = (aa > rr) && (ab > aa) && (ac > aa);
	bool sep2 = (bb > rr) && (ab > bb) && (bc > bb);
	bool sep3 = (cc > rr) && (ac > cc) && (bc > cc);
	// end vertex checks

	// begin edge tests
	glm::vec3 AB = b - a;
	glm::vec3 BC = c - b;
	glm::vec3 CA = a - c;
	float d1 = ab - aa;
	float d2 = bc - bb;
	float d3 = ac - cc;
	float e1 = glm::dot(AB, AB);
	float e2 = glm::dot(BC, BC);
	float e3 = glm::dot(CA, CA);
	glm::vec3 Q1 = (a * e1) - (AB * d1);
	glm::vec3 Q2 = (b * e2) - (BC * d2);
	glm::vec3 Q3 = (c * e3) - (CA * d3);
	glm::vec3 QC = (c * e1) - Q1;
	glm::vec3 QA = (a * e2) - Q2;
	glm::vec3 QB = (b * e3) - Q3;
	bool sep4 = (glm::dot(Q1, Q1) > rr * e1 * e1) && (glm::dot(Q1, QC) > 0);
	bool sep5 = (glm::dot(Q2, Q2) > rr * e2 * e2) && (glm::dot(Q2, QA) > 0);
	bool sep6 = (glm::dot(Q3, Q3) > rr * e3 * e3) && (glm::dot(Q3, QB) > 0);
	//end edge tests

	return !(sep1 || sep2 || sep3 || sep4 || sep5 || sep6);
}

bool intersects(const AABB &first, const AABB &second)
{
	return (first.xMin < second.xMax && first.xMax > second.xMin &&
			first.yMin < second.yMax && first.yMax > second.yMin &&
			first.zMin < second.zMax && first.zMax > second.zMin);
}

bool brokenIntersection(const AABB &first, const Capsule3D &second)
{
	glm::vec3 top_topLeft(first.xMin, first.yMax, first.zMin);
	glm::vec3 top_topRight(first.xMax, first.yMax, first.zMin);
	glm::vec3 top_bottomLeft(first.xMin, first.yMax, first.zMax);
	glm::vec3 top_bottomRight(first.xMax, first.yMax, first.zMax);
	glm::vec3 bottom_topLeft(first.xMin, first.yMin, first.zMin);
	glm::vec3 bottom_topRight(first.xMax, first.yMin, first.zMin);
	glm::vec3 bottom_bottomLeft(first.xMin, first.yMin, first.zMax);
	glm::vec3 bottom_bottomRight(first.xMax, first.yMin, first.zMax);

	// Test the difference faces
	Polygon3 top(std::vector<glm::vec3>{ top_topLeft, top_topRight, top_bottomRight, top_bottomLeft});
	Polygon3 bottom(std::vector<glm::vec3>{ bottom_topLeft, bottom_topRight, bottom_bottomRight, bottom_bottomLeft});
	Polygon3 left(std::vector<glm::vec3>{ top_topLeft, top_bottomLeft, bottom_bottomLeft, bottom_topLeft});
	Polygon3 right(std::vector<glm::vec3>{ top_topRight, top_bottomRight, bottom_bottomRight, bottom_topRight});
	Polygon3 back(std::vector<glm::vec3>{ top_topLeft, top_topRight, bottom_topRight, bottom_topLeft});
	Polygon3 front(std::vector<glm::vec3>{ top_bottomLeft, top_bottomRight, bottom_bottomRight, bottom_bottomLeft});

	LineSegment3 seg(second.point1, second.point2);
	if (intersects(top, seg))
	{
		return true;
	}
	if (intersects(bottom, seg))
	{
		return true;
	}
	if (intersects(left, seg))
	{
		return true;
	}
	if (intersects(right, seg))
	{
		return true;
	}
	if (intersects(front, seg))
	{
		return true;
	}
	if (intersects(back, seg))
	{
		return true;
	}
	return false;
}
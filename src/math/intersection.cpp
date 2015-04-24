#include <iostream>
#include <stdexcept>
#include <sstream>
#include "intersection.h"

bool intersects(const Triangle3 &triangle, const LineVariant3 &line)
{
	auto plane = triangle.getPlane();
	if (!line.intersectsPlane(plane))
		return false;
	return intersects(plane, triangle.point1, triangle.point2, triangle.point3, true, line);
}

bool intersects(const Polygon3 &polygon, const LineVariant3 &line)
{
	bool coplanar = false;
	if (polygon.isCoplanar)
	{
		if (!line.intersectsPlane(polygon.getPlane()))
			return false;
		coplanar = true;
	}

	for (int i = 0; i < static_cast<int>(polygon.points.size()) - 2; i++)
	{
		if (intersects(polygon.getPlane(), polygon.points.at(i), polygon.points.at(i + 1), polygon.points.at(i + 2), coplanar, line))
		{
			return true;
		}
	}
	return false;
}

bool intersects(const Plane3 &plane, const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, bool coplanar, const LineVariant3 &line)
{
	std::shared_ptr<glm::vec3> p2;
	if (!coplanar)
	{
		Plane3 plane(v0, v1, v2);
		if (!line.intersectsPlane(plane))
			return false;
		else
			p2 = intersection(plane, line);
	}
	else
	{
		p2 = intersection(plane, line);
		if (!p2)
			return false;
	}

	glm::vec3 u = v1 - v0;
	glm::vec3 v = v2 - v0;
	glm::vec3 w = (*p2) - v0;

	double denom = pow(glm::dot(u, v), 2) - (glm::dot(u, u) * glm::dot(v, v));
	double s = ((glm::dot(u, v) * glm::dot(w, v)) - (glm::dot(v, v) * glm::dot(w, u))) / denom;
	double t = ((glm::dot(u, v) * glm::dot(w, u)) - (glm::dot(u, u) * glm::dot(w, v))) / denom;
	if (s >= 0 && t >= 0 && s + t <= 1) return true;
	return false;
}

std::unique_ptr<glm::vec3> intersection(const Triangle3 &triangle, const LineVariant3 &line)
{
	if (intersects(triangle, line))
	{
		return intersection(triangle.getPlane(), line);
	}
	return nullptr;
}

std::unique_ptr<glm::vec3> intersection(const Polygon3 &polygon, const LineVariant3 &line)
{
	if (intersects(polygon, line))
	{
		double r1 = glm::dot(polygon.normal, polygon.getPlane().pointOnPlane - line.getPoint());
		r1 = r1 / glm::dot(polygon.normal, line.getDirection());
		glm::vec3 pointp = line.getPoint();
		glm::vec3 store = line.getDirection();
		glm::vec3 temp = pointp + (glm::vec3(store.x * r1, store.y * r1, store.z * r1));
		return std::unique_ptr<glm::vec3>(new glm::vec3(temp.x, temp.y, temp.z));
	}
	return nullptr;
}




bool intersects(const Plane3 &plane, const LineSegment3 &line)
{
	if (glm::dot(line.getDirection(), plane.normal) == 0)
	{
		return false;
	}
	double r1 = glm::dot(plane.normal, plane.pointOnPlane - line.getPoint());
	r1 = r1 / glm::dot(plane.normal, line.getDirection());
	return (r1 >= 0 && r1 <= 1);
}

bool intersects(const Plane3 &plane, const Line3 &line)
{
	if (glm::dot(line.getDirection(), plane.normal) == 0)
	{
		return false;
	}
	return true;
}

bool intersects(const Plane3 &plane, const Ray3 &line)
{
	if (glm::dot(line.getDirection(), plane.normal) == 0)
	{
		return false;
	}
	double r1 = glm::dot(plane.normal, plane.pointOnPlane - line.getPoint());
	r1 = r1 / glm::dot(plane.normal, line.getDirection());
	return r1 >= 0;
}

std::unique_ptr<glm::vec3> intersection(const Plane3 &plane, const LineVariant3 &line)
{
	if (line.intersectsPlane(plane))
	{
		glm::vec3 pointp = line.getPoint();
		glm::vec3 store = line.getDirection();
		double r1 = glm::dot(plane.normal, plane.pointOnPlane - pointp);
		r1 = r1 / glm::dot(plane.normal, store);
		return std::unique_ptr<glm::vec3>(new glm::vec3(pointp.x + store.x * r1, pointp.y + store.y * r1, pointp.z + store.z * r1));
	}
	return std::unique_ptr<glm::vec3>(nullptr);
}

bool intersects(const Triangle3 &first, const Triangle3 &second)
{
	return (intersects(first.getPlane(), second) && intersects(second.getPlane(), first));
}

bool intersects(const Plane3 &plane, const Polygon3 &poly)
{
	//Stores the difference in number of verts on either side of a plane
	// a negative number implies more points are beneath than above
	int count = 0;
	for (int i = 0; i < static_cast<int>(poly.points.size()); i++)
	{
		double normalDotDisplacement = glm::dot(plane.normal, poly.points.at(i) - plane.pointOnPlane);
		if (normalDotDisplacement > 0)
		{
			count++;
		}
		else if (normalDotDisplacement < 0)
		{
			count--;
		}

	}
	if (abs(count) != static_cast<int>(poly.points.size()))
	{
		return true;
	}
	return false;
}

bool intersects(const Plane3 &plane, const Triangle3 &poly)
{
	//Stores the difference in number of verts on either side of a plane
	// a negative number implies more points are beneath than above
	int count = 0;

	double normalDotDisplacement = glm::dot(plane.normal, poly.point1 - plane.pointOnPlane);
	if (normalDotDisplacement > 0)
		count++;
	else if (normalDotDisplacement < 0)
		count--;

	normalDotDisplacement = glm::dot(plane.normal, poly.point2 - plane.pointOnPlane);
	if (normalDotDisplacement > 0)
		count++;
	else if (normalDotDisplacement < 0)
		count--;

	normalDotDisplacement = glm::dot(plane.normal, poly.point3 - plane.pointOnPlane);
	if (normalDotDisplacement > 0)
		count++;
	else if (normalDotDisplacement < 0)
		count--;
	
	return (abs(count) != 3);
}

bool intersects(const Polygon3 &first, const Polygon3 &second)
{
	return (intersects(first.getPlane(), second) && intersects(second.getPlane(), first));
}
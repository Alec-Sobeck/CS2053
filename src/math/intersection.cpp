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

std::unique_ptr<glm::vec2> intersection(const LineSegment2 &first, const LineSegment2 &second)
{
	//Solution adapted from http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	//Q is the tail of the first line segment, P is the tail of the second line segment,
	//S is the first line segment as a Vector, R is the second line segment as a Vector
	glm::vec2 q = first.point1;  //q
	glm::vec2 s = first.point2 - first.point1; //s
	glm::vec2 p = second.point1; //p
	glm::vec2 r = second.point2 - second.point1;  //r

	//    	2D cross product for v×w, which would be the magnitude of the 3D cross product. This yields a double not another Vector.
	//    	v.x * w.y − v.y * w.x

	//		LineSegments intersect if the following equality holds true: 
	//    	p + t*r = q + u*s
	//    	where t,u are scalars and p,q,r,s are vectors:
	//    	t = (q − p) × s / (r × s)
	//    	u = (q − p) × r / (r × s)
	//      
	//Calculate a bunch of the terms in the formula
	glm::vec2 qMinusP = q - p;
	float qMinusPCrossedWithS = qMinusP.x * s.y - qMinusP.y * s.x;
	float qMinusPCrossedWithR = qMinusP.x * r.y - qMinusP.y * r.x;
	float rCrossedWithS = r.x * s.y - r.y * s.x;

	//Check to make sure the there wont be a division by zero. Due to doubles, it cant be a check for equality. 
	if (!approximatelyEqual(rCrossedWithS, 0))
	{
		//Solve for t and u
		float t = qMinusPCrossedWithS / rCrossedWithS;
		float u = qMinusPCrossedWithR / rCrossedWithS;
		if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
		{
			glm::vec2 v = p + (r * t);
			glm::vec2 v1 = q + (s * u);
			//If the vectors are equal, then the line segments have intersected at that point/.
			if (v == v1)
			{
				return std::unique_ptr<glm::vec2>(new glm::vec2(v.x, v.y));
			}
		}
	}
	return nullptr;
}

bool intersects(const Rectangle2 &first, const Rectangle2 &second)
{
	return separatingaxistest::intersects(first, second);
}

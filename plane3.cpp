
#include <sstream>
#include <cmath>
#include "plane3.h"
#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "gamemath.h"	
#include "linesegment3.h"
#include "line3.h"
#include "ray3.h"

Plane3::Plane3(glm::vec3 pointOnPlane, glm::vec3 normal) : pointOnPlane(pointOnPlane), normal(normal)
{
}

Plane3::Plane3(glm::vec3 pointOnPlane, std::vector<glm::vec3> directions) : 
//TODO ensure this calculation works properly
	pointOnPlane(pointOnPlane)
{
	normal = glm::cross(directions.at(0), glm::normalize(directions.at(1)));
}

Plane3::Plane3(double a, double b, double c, double d)
{
	normal = glm::vec3(a, b, c);
	if (!approximatelyEqual(static_cast<float>(normal.length()), 1))
	{
		std::stringstream ss;
		ss << "Currently, this constructor requires that the normal defined by the equation be of unit length. The provided normal " <<
			"in this case is of length " << normal.length() << ". (This functionality" << " will hopefully be fixed later)";
		throw std::invalid_argument(ss.str());
	}
	pointOnPlane = glm::vec3(-d * normal.x, -d * normal.y, -d * normal.z);
}

Plane3::Plane3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	//TODO test this calculation works
	pointOnPlane = point1;
	glm::vec3 first = point2 - point1;
	glm::vec3 second = point3 - point1;
	if (parallel(first, second))
	{
		throw std::invalid_argument("Co-linear points are not allowed.");
	}
	normal = glm::cross(first, second);
}

bool Plane3::isPerpendicular(glm::vec3 other)
{
	return parallel(normal, other);
}

bool Plane3::does_intersect_line(ILineVariant &line){
	if (glm::dot(line.getDirection(), getNormal()) == 0)
	{
		return false;
	}
	else 
	{
		if (dynamic_cast<Line3*>(&line) != 0)
		{
			return true;
		}
		double r1 = glm::dot(getNormal(), getPointOnPlane() - line.getPoint());
		r1 = r1 / glm::dot(getNormal(), line.getDirection());
		if (r1 >= 0)
		{
			if (dynamic_cast<LineSegment3*>(&line) != 0 && r1 <= 1)
			{
				return true;
			}
			else if (dynamic_cast<Ray3*>(&line) != nullptr)
			{
				return true;
			}
			return false;
		}
		else return false;
	}
}

bool Plane3::doesIntersectPoly(Polygon3 &poly)
{
	//Stores the difference in number of verts on either side of a plane
	// a negative number implies more points are beneath than above
	int count = 0;
	for (int i = 0; i < static_cast<int>(poly.points.size()); i++)
	{
		double normalDotDisplacement = glm::dot(normal, poly.points[i] - pointOnPlane);
		if (normalDotDisplacement > 0)
		{
			count++;
		}
		else if (normalDotDisplacement < 0)
		{
			count--;
		}

	}
	if (abs(count) != poly.points.size()) 
		return true;
	return false;
}

std::shared_ptr<glm::vec3> Plane3::lineIntersectPoint(ILineVariant &line)
{
	if (does_intersect_line(line))
	{
		double r1 = glm::dot(getNormal(), getPointOnPlane() - line.getPoint());
		r1 = r1 / glm::dot(getNormal(), line.getDirection());
		glm::vec3 pointp = (glm::vec3)line.getPoint();
		glm::vec3 store(line.getDirection());
		glm::vec3 temp = pointp + (glm::vec3(store.x * r1, store.y * r1, store.z * r1));
		return std::shared_ptr<glm::vec3>(new glm::vec3(temp.x, temp.y, temp.z));
	}
	else
	{
		return std::shared_ptr<glm::vec3>(nullptr);
	}
}

glm::vec4 Plane3::getGeneralEquation()
{
	return glm::vec4(normal.x, normal.y, normal.z, -(glm::dot(normal, pointOnPlane)));
}

double Plane3::distanceToPoint(glm::vec3 vector)
{
	glm::vec4 planeEquation = getGeneralEquation();

	double result = planeEquation.x * vector.x +
		planeEquation.y * vector.y +
		planeEquation.z * vector.z +
		planeEquation.w;

	result /= glm::length(planeEquation); 
	return result;
}

glm::vec3 Plane3::getNormal()
{
	return normal;
}

glm::vec3 Plane3::getUnitNormal()
{
	return glm::normalize(normal);
}

glm::vec3 Plane3::getPointOnPlane()
{
	return Plane3::pointOnPlane;
}

std::string Plane3::toString()
{
	std::stringstream ss;
	ss << "Plane3[point=<" << pointOnPlane.x << "," << pointOnPlane.y << "," << pointOnPlane.z << ">, normal=<" 
		<< normal.x << ", " << normal.y << ", " << normal.z << ">]";
	return ss.str();
}


#include <cmath>
#include <stdexcept>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "polygon3.h"
#include "gamemath.h"

Polygon3::Polygon3(std::vector<glm::vec3> points)
{
    if(points.size() < 3)
    {
        std::stringstream ss;
        ss << "Polygon3 must have at least 3 vertices to be defined: given " << points.size();
        throw std::invalid_argument(ss.str());
    }
    this->points = points;
    computeNormal();
    computeIsCoplanar();
	if (!isCoplanar)
	{
		throw std::invalid_argument("A Polygon3 must be coplanar. The provided glm::vec3[] does not describe a coplanar polygon.");
	}
}

void Polygon3::computeIsCoplanar() {
	for (int i = 2; i < static_cast<int>(points.size()); i++){
        if (!approximatelyEqual(glm::dot(normal, points[i] - points[0]), 0)){
            isCoplanar = false;
            return;
        }
    }
    isCoplanar = true;
}

void Polygon3::computeNormal()
{
    glm::vec3 firstSide = points[1] - points[0];
    glm::vec3 secondSide = points[1] - points[2];
    normal = glm::cross(firstSide, secondSide);
}

void Polygon3::cullNthPoint(int n){
	if (n > static_cast<int>(points.size()))
    {
        std::stringstream ss;
        ss << "Index not in range of the points array: " << n;
        throw std::invalid_argument(ss.str());
    }
    if(n == 3)
        throw std::logic_error("Culling a point from this Polygon3 would make the polygon degenerate.");

    std::vector<glm::vec3> replacement;
    replacement.reserve(points.size() - 1);
    for (int i = 0; i < static_cast<int>(points.size()); i++){
        if (i < n){
            replacement[i] = points[i];
        }
        else if (i > n){
            replacement[i-1] = points[i];
        }
    }
    this->points = replacement;
}

glm::vec3 Polygon3::getNormal(){
    return normal;
}

glm::vec3 Polygon3::getUnitNormal(){
	return glm::normalize(normal);
}

double Polygon3::area() {
    // TODO: test this more thoroughly
    if (isCoplanar && points.size() >= 3)
	{
        glm::vec3 total(0, 0, 0);
		for (int i = 0; i < static_cast<int>(points.size()); i++) 
		{
            glm::vec3 vi1 = points[i];
            glm::vec3 vi2;
            if (i == points.size() - 1)
                vi2 = points[0];
            else
                vi2 = points[i + 1];
            glm::vec3 prod = glm::cross(vi1, vi2);
            total = glm::vec3(total.x + prod.x, total.y + prod.y, total.z + prod.z);
        }
		double result = glm::dot(total, glm::normalize(normal));
        return abs(result / 2);
    }
    return -1;
}

Plane3 Polygon3::getPlane()
{
    if (!isCoplanar || (normal.x == 0 && normal.y == 0 && normal.z == 0)/*normal == null*/)
	{
		throw std::invalid_argument("No plane exists for this Polygon3.");
    }
    return Plane3(points.at(0), normal);
}

bool Polygon3::does_intersect_line(ILineVariant &line)
{
    bool coplanar = false;
    if (isCoplanar)
	{
        if (!getPlane().does_intersect_line(line))
            return false;
        coplanar = true;
    }

	for (int i = 0; i < static_cast<int>(points.size()) - 2; i++)
	{
        if (line_does_intersect_triangle(points.at(i), points.at(i + 1), points.at(i + 2), coplanar, line))
		{
            return true;
        }
    }
    return false;
}

bool Polygon3::line_does_intersect_triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool coplanar, ILineVariant &line){
    std::shared_ptr<glm::vec3> p2;
    if (!coplanar)
	{
        Plane3 plane(v0, v1, v2);
        if (!plane.does_intersect_line(line)) 
			return false;
        else 
			p2 = plane.lineIntersectPoint(line);
    }
    else
	{
		std::shared_ptr<glm::vec3> point = getPlane().lineIntersectPoint(line);
        if(point == nullptr)
            return false;
        p2 = point;
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

std::shared_ptr<glm::vec3> Polygon3::line_intersect_point(ILineVariant &line){
    if (does_intersect_line(line))
	{
        return getPlane().lineIntersectPoint(line);
	}
	else
	{
		return std::shared_ptr<glm::vec3>(nullptr);
	}
}

bool Polygon3::does_intersect_poly(Polygon3 poly){
    return (getPlane().doesIntersectPoly(poly) && poly.getPlane().doesIntersectPoly(*this));
}

std::vector<glm::vec3> Polygon3::getVertices()
{
    return points;
}

int Polygon3::getVertexCount()
{
    return points.size();
}

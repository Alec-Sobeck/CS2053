#include <iostream>
#include <stdexcept>
#include <sstream>
#include "math/polygon3.h"
#include "math/gamemath.h"

Polygon3::Polygon3(std::vector<glm::vec3> points) : points(points)
{
    if(points.size() < 3)
    {
        std::stringstream ss;
        ss << "Polygon3 must have at least 3 vertices to be defined: given " << points.size();
        throw std::invalid_argument(ss.str());
    }
    computeNormal();
    computeIsCoplanar();
	if (!isCoplanar)
	{
		throw std::invalid_argument("A Polygon3 must be coplanar. The provided glm::vec3[] does not describe a coplanar polygon.");
	}
}

void Polygon3::computeIsCoplanar()
{
	for (int i = 2; i < static_cast<int>(points.size()); i++)
	{
        float val = glm::dot(normal, points[i] - points[0]);
        if (fabs(val) > 0.01)
        {
            std::cout << points.size() << std::endl;
            std::cout << glm::dot(normal, points[i] - points[0]) << std::endl;
            std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
            std::cout << (points[i] - points[0]).x << " " <<
            (points[i] - points[0]).y << " "
             << (points[i] - points[0]).z << " " << std::endl;
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
    normal = glm::normalize(glm::cross(firstSide, secondSide));
}

void Polygon3::cullNthPoint(int n)
{
	if (n >= points.size() || n < 0)
    {
        std::stringstream ss;
        ss << "Index not in range of the points array: " << n;
        throw std::invalid_argument(ss.str());
    }
	if (n == 3)
	{
		throw std::logic_error("Culling a point from this Polygon3 would make the polygon degenerate.");
	}

	points.erase(points.begin() + n);
}

double Polygon3::area() 
{
    if (isCoplanar && points.size() >= 3)
	{
        glm::vec3 total(0, 0, 0);
		for (int i = 0; i < static_cast<int>(points.size()); i++)
		{
            glm::vec3 vi1 = points[i];
            glm::vec3 vi2;
            if (i == static_cast<int>(points.size()) - 1)
            {
                vi2 = points[0];
            }
            else
            {
                vi2 = points[i + 1];
            }
            glm::vec3 prod = glm::cross(vi1, vi2);
            total = glm::vec3(total.x + prod.x, total.y + prod.y, total.z + prod.z);
        }
		double result = glm::dot(total, glm::normalize(normal));
        return abs(result / 2);
    }
    return -1;
}

Plane3 Polygon3::getPlane() const
{
    if (!isCoplanar || (normal.x == 0 && normal.y == 0 && normal.z == 0)/*normal == null*/)
	{
		throw std::invalid_argument("No plane exists for this Polygon3.");
    }
    return Plane3(points.at(0), normal);
}

int Polygon3::vertexCount() const
{
    return points.size();
}

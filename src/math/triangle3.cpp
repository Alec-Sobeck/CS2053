#include <iostream>
#include <stdexcept>
#include <sstream>
#include "math/triangle3.h"
#include "math/gamemath.h"

Triangle3::Triangle3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3) : point1(point1), point2(point2), point3(point3)
{
    computeNormal();
}

void Triangle3::computeNormal()
{
    glm::vec3 firstSide = point2 - point1;
    glm::vec3 secondSide = point2 - point3;
    normal = glm::normalize(glm::cross(firstSide, secondSide));
}

float Triangle3::area() const
{  
    glm::vec3 total = glm::cross(point1, point2) + glm::cross(point2, point3) + glm::cross(point3, point1);
	float result = glm::dot(total, normal);
    return abs(result / 2);
}

Plane3 Triangle3::getPlane() const
{
    return Plane3(point1, normal);
}

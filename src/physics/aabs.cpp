
#include <cmath>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "physics/aabs.h"
#include "math/polygon3.h"
#include "math/gamemath.h"


AABS::AABS(float x, float y, float z, float radius) : x(x), y(y), z(z), radius(radius)
{
}

float AABS::surfaceArea()
{
    return 4.0f * PI * radius * radius;
}

float AABS::volume()
{
    return 1.33333333333f * PI * radius * radius * radius;
}

bool AABS::overlaps(AABS &other)
{
    return (pow(x - other.x, 2) +
            pow(y - other.y, 2) +
            pow(z - other.z, 2)) < pow(radius + other.radius, 2);
}

bool AABS::intersectsTriangle(Polygon3 &triangle)
{
    if (triangle.getVertexCount() != 3)
    {
        // Provided Polygon3 is not a triangle
        return false;
    }
    // If the sphere is further away from the plane than its radius, it can not collide, fail-fast.
    if (triangle.getPlane().distanceToPoint(glm::vec3(x, y, z)) >= this->radius)
    {
        return false;
    }

    // Begin vertex checks
    glm::vec3 a = triangle.getVertices()[0];
    glm::vec3 b = triangle.getVertices()[1];
    glm::vec3 c = triangle.getVertices()[2];

    float aa = glm::dot(a, a);
    float ab = glm::dot(a, b);
    float ac = glm::dot(a, c);
    float bb = glm::dot(b, b);
    float bc = glm::dot(b, c);
    float cc = glm::dot(c, c);
    float rr = this->radius * this->radius;

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

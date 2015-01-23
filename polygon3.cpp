
#include <stdexcept>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "polygon3.h"
#include "gamemath.h"

Polygon3::Polygon3(std::vector<glm::vec3> points) {
    if(points.size() < 3)
    {
        std::stringstream ss;
        ss << "Polygon3 must have at least 3 vertices to be defined: given " << points.size();
        throw std::invalid_argument(ss.str());
    }
    this->points = points;
    computeNormal();
    computeIsCoplanar();
    if(!isCoplanar)
        throw std::invalid_argument("A Polygon3 must be coplanar. The provided glm::vec3[] does not describe a coplanar polygon.");
}

void Polygon3::computeIsCoplanar() {
    for (int i = 2; i < points.size(); i++){
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
    if(n > points.size())
    {
        std::stringstream ss;
        ss << "Index not in range of the points array: " << n;
        throw std::invalid_argument(ss.str());
    }
    if(n == 3)
        throw std::logic_error("Culling a point from this Polygon3 would make the polygon degenerate.");

    std::vector<glm::vec3> replacement;
    replacement.reserve(points.size() - 1);
    for (int i = 0; i < points.size(); i++){
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
    return normal.normalize();
}

double Polygon3::area() {
    // TODO: test this more thoroughly
    if (isCoplanar && points.length >= 3) {
        glm::vec3 total = new glm::vec3();
        for (int i = 0; i < points.length; i++) {
            glm::vec3 vi1 = points[i];
            glm::vec3 vi2;
            if (i == points.length - 1)
                vi2 = points[0];
            else
                vi2 = points[i + 1];
            glm::vec3 prod = vi1.crossProduct(vi2);
            total = new glm::vec3(total.getX() + prod.getX(), total.getY() + prod.getY(), total.getZ() + prod.getZ());
        }
        double result = total.dot(normal.normalize());
        return Math.abs(result / 2);
    }
    return -1;
}

Plane3 Polygon3::getPlane(){
    if (!this.isCoplanar || this.normal == null){
        return null;
    }
    return new Plane3(points[0], this.normal);
}

bool Polygon3::does_intersect_line(ILineVariant line){
    bool coplanar = false;
    if (this.isCoplanar){
        if (!this.getPlane().does_intersect_line(line))
            return false;
        coplanar = true;
    }

    for(int i = 0; i < this.points.length - 2; i++){
        if (line_does_intersect_triangle(this.points[i], this.points[i+1], this.points[i + 2], coplanar, line)){
            return true;
        }
    }
    return false;
}

bool Polygon3::line_does_intersect_triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool coplanar, ILineVariant line){
    glm::vec3 p2;
    if (!coplanar){
        Plane3 plane = new Plane3(v0, v1, v2);
        if (!plane.does_intersect_line(line)) return false;
        else p2 = plane.lineIntersectPoint(line);
    }
    else{
        glm::vec3 point = this.getPlane().lineIntersectPoint(line);
        if(point == null)
            return false;
        p2 = point;
    }

    glm::vec3 u = v1.subtract(v0).asglm::vec3();
    glm::vec3 v = v2.subtract(v0).asglm::vec3();
    glm::vec3 w = p2.subtract(v0).asglm::vec3();

    double denom = Math.pow(u.dot(v), 2) - (u.dot(u) * v.dot(v));
    double s = ((u.dot(v) * w.dot(v)) - (v.dot(v) * w.dot(u)))/denom;
    double t = ((u.dot(v) * w.dot(u)) - (u.dot(u) * w.dot(v)))/denom;
    if (s >= 0 && t >= 0 && s + t <= 1) return true;
    return false;
}

glm::vec3 Polygon3::line_intersect_point(ILineVariant line){
    if (does_intersect_line(line)){
        return this.getPlane().lineIntersectPoint(line);
    }
    else return null;
}

bool Polygon3::does_intersect_poly(Polygon3 poly){
    return (this.getPlane().doesIntersectPoly(poly) && poly.getPlane().doesIntersectPoly(this));
}

std::vector<glm::vec3> Polygon3::getVertices()
{
    return points;
}

int Polygon3::getVertexCount()
{
    return points.size();
}

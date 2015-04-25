#ifndef POLYGON_MATH_H
#define POLYGON_MATH_H

#include "gamemath.h"

///
/// Polygonmath contains functions which operate on 2D or 3D polygons. A neat perk of a lot of these calculations is that they accept lists of points, which means 
/// that they can operate on arbitrarily defined polygon specializations like a triangle2, rectangle2, or hexagon2 with no modifications.
///


///
/// Determines if a specified (x,y) tuple is inside the 2D polygon 
/// See: http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
/// \param testx a double which is the X coordinate of the test point
/// \param testy a double which is the Y coordinate of the test point
/// \return a bool, true if the point specified is inside the Polygon2, otherwise false
///
bool containsPoint(const std::vector<glm::vec2> &points, glm::vec2 point);

///
/// Rotates the polygon, permanently, on a vertex as specified by the given angleOfRotation and vertexIndex.
/// \param vertexIndex an int, which determines which vertex to rotate on. The vertex rotated on will be
/// points[vertexIndex]. This must be in range 0 <= vertexIndex < vertex_count or a bounds exception will be thrown.
/// param angleOfRotation a double, describing the angle of rotation of this operation, in radians.
/// A positive value will rotate counter-clockwise while a negative value will rotate clock-wise.
///
void rotateOnVertex(std::vector<glm::vec2> &points, int vertexIndex, double angleOfRotation);

///
/// Rotates this Polygon2 around an arbitrary vec2. This vec2 need not be a vertex of the polygon2 nor the origin (0,0).
/// \param pointRotatedOn a Vector2 to rotate this Polygon2 on, which need not be a vertex of the Polygon2
/// \param angleOfRotation a double, describing the angle of rotation of this operation, in radians.
/// A positive value will rotate counter-clockwise while a negative value will rotate clock-wise.
/// 
void rotateOnPoint(std::vector<glm::vec2> &points, glm::vec2 pointRotatedOn, double angleOfRotation);

///
/// Gets normals to the sides of this Polygon2, which means there should be an equal number of normals to
/// vertices for this polygon.
/// \return a std::vector<glm::vec2> containing the normal vectors to the sides of this polygon
///
std::vector<glm::vec2> getNormals(const std::vector<glm::vec2> &points);


#endif

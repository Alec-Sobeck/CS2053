#pragma once

class Rectangle2;

#include <vector>
#include "math/plane3.h"
#include "math/triangle3.h"
#include "math/gamemath.h"
#include "math/line3.h"
#include "math/ray3.h"
#include "math/plane3.h"
#include "math/linesegment3.h"
#include "math/linesegment2.h"
#include "math/rectangle2.h"
#include "separatingaxistest.h"

bool intersects(const Triangle3 &first, const Triangle3 &second); 
bool intersects(const Triangle3 &triangle, const LineVariant3 &line);
bool intersects(const Polygon3 &polygon, const LineVariant3 &line);
bool intersects(const Plane3 &plane, const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, bool coplanar, const LineVariant3 &line);
std::unique_ptr<glm::vec3> intersection(const Triangle3 &triangle, const LineVariant3 &line);
///
/// Returns the specific point at which the plane and the provided line variant intersect.
/// Returns nullptr if no intersection occurs.
/// \param line - the line variant against which to check
/// \return A glm::vec3 representing the point on the plane at which the line variant intersects. nullptr if no intersection occurs.
///
std::unique_ptr<glm::vec3> intersection(const Polygon3 &polygon, const LineVariant3 &line);
///
/// Returns the specific point at which the plane and the provided line variant intersect.
/// Returns NULL if no intersection occurs.
/// \param line - the line variant against which to check
/// \return A glm::vec3 representing the point on the plane at which the line variant intersects. nullptr if no intersection occurs.
///
std::unique_ptr<glm::vec3> intersection(const Plane3 &plane, const LineVariant3 &line);

bool intersects(const Plane3 &plane, const LineSegment3 &line);
bool intersects(const Plane3 &plane, const Line3 &line);
bool intersects(const Plane3 &plane, const Ray3 &line);
///
/// Returns true if the provided polygon intersects with the plane
/// \param poly the polygon against which to check
/// \return a bool representing if the poly intersects the plane
///
bool intersects(const Plane3 &plane, const Polygon3 &poly);
bool intersects(const Plane3 &plane, const Triangle3 &poly);
bool intersects(const Polygon3 &first, const Polygon3 &second);
std::unique_ptr<glm::vec2> intersection(const LineSegment2 &first, const LineSegment2 &second);

///
/// Tries to determine whether or not this Rectangle2 intersects with the provided Rectangle2. This relies on a call
/// to SeparatingAxisTestHelper to help determine whether or not the rectangles overlap. If for some reason
/// a Rectangle2 is not convex or has distorted vertices then this test may fail to yield correct results.
/// \param other another Rectangle2 to test for overlap with this Rectangle2
/// \return a bool, which indicates if the provided Rectangle2 overlaps with this Rectangle2
///
bool intersects(const Rectangle2 &first, const Rectangle2 &second);


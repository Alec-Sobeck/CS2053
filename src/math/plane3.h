#pragma once

#include <string>
#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "math/polygon3.h"

///
/// Plane3 implements a plane that exists in the third dimension.A plane can be
/// defined by either 3 or more points that are not all co - linear, 2 direction vectors
/// and a point, or a normal and a point on the plane. Plane3 will accept any of those
/// when constructing the Plane3, but stores only a point on the plane and the normal.
/// \author      Alec Sobeck
/// \author      Matthew Robertson
///
class Plane3
{
public:
	/// 
	/// Constructs a new Plane3 with the provided glm::vec3 and glm::vec3, performing only a calculation
	/// to normalize the provided glm::vec3.
	/// \param pointOnPlane a glm::vec3 that is on the plane
	/// \param normal a glm::vec3 that is normal(thusly perpendicular) to the plane
	/// 
	Plane3(glm::vec3 pointOnPlane, glm::vec3 normal);
	/// 
	/// Constructs a new Plane3 with the provided glm::vec3 and direction vectors. A computation
	/// will be done to find the normal to this plane.
	/// \param pointOnPlane a glm::vec3 that is on the plane somewhere
	/// \param directions a std::vector<glm::vec3> containing two distinct direction vectors which are on this plane.
	///
	Plane3(glm::vec3 pointOnPlane, std::vector<glm::vec3> directions);
	/// 
	/// Creates a plane using the scalar equation for a plane ax + by + cz = d.
	/// \param a a double representing a in the above equation.
	/// \param b a double representing b in the above equation.
	/// \param c a double representing c in the above equation.
	/// \param d a double representing d in the above equation.
	///
	Plane3(float a, float b, float c, float d);
	///
	/// Constructs a new Plane3 with the provided glm::vec3 and direction vectors. A computation
	/// will be done to find the normal to this plane. co-linear points will cause an
	/// std::illegal_argument exception to be thrown.
	/// \param point1 a first distinct glm::vec3 that is on the plane somewhere
	/// \param point2 a second distinct glm::vec3 that is on the plane somewhere
	/// \param point3 a third distinct glm::vec3 that is on the plane somewhere
	/// 
	Plane3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	/// 
	/// Checks to see if a glm::vec3 is perpendicular to this Plane3. This condition is met should
	/// the provided glm::vec3 be parallel to the normal of this plane.
	/// \param other a glm::vec3 to check against this Plane3 to see if it is perpendicular
	/// \return a bool, true if the provided glm::vec3 is perpendicular to this Plane3; otherwise false
	/// 
	bool isPerpendicular(glm::vec3 other);	
	/// 
	/// Returns a general equation for the plane as a Vector4, in the form <a,b,c,d>
	/// for the equation aX + bY + cZ + d = 0
	/// \return a vec4 representing the plane equation
	///
	glm::vec4 getGeneralEquation();
	/// 
	/// Gets the signed distance between the plane and the provided vector
	/// \param vector the glm::vec3 to calculate the distance for
	/// \return the distance between the point and the plane
	///
	float distanceToPoint(glm::vec3 vector);	
	/// 
	/// A normal to the plane, which is therefore by definition parallel to the plane.
	/// This will be normalized on plane creation. 
	/// 
	glm::vec3 normal;
	///  
	/// A point that is somewhere on the plane. Required to define the plane properly.
	/// 
	glm::vec3 pointOnPlane;
};


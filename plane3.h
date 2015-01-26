#ifndef PLANE3_H
#define PLANE3_H

class Polygon3;

#include <string>
#include <memory>
#include <vector>
#include "glm/vec3.hpp"
#include "ilinevariant.h"
#include "polygon3.h"

/**
 * Plane3 implements a plane that exists in the third dimension. A plane can be
 * defined by either 3 or more points that are not all co-linear, 2 direction vectors
 * and a point, or a normal and a point on the plane. Plane3 will accept any of those
 * when constructing the Plane3, but stores only a point on the plane and the normal.
 * <br><br>
 * Plane3 are immutable.
 * @author      Alec Sobeck
 * @author      Matthew Robertson
 * @version     1.0
 * @since       1.0
 */
class Plane3
{
public:
	/**
	 * Constructs a new Plane3 with the provided glm::vec3 and glm::vec3, performing only a calculation
	 * to normalize the provided glm::vec3.
	 * @param pointOnPlane a glm::vec3 that is on the plane
	 * @param normal a glm::vec3 that is normal(thusly perpendicular) to the plane
	 */
	Plane3(glm::vec3 pointOnPlane, glm::vec3 normal);
	/**
	 * Constructs a new Plane3 with the provided glm::vec3 and direction vectors. A computation
	 * will be done to find the normal to this plane.
	 * @param pointOnPlane a glm::vec3 that is on the plane somewhere
	 * @param directions a glm::vec3[] containing two distinct direction vectors which are on this plane.
	 */
	Plane3(glm::vec3 pointOnPlane, std::vector<glm::vec3> directions);
	/**
	 * Creates a plane using the scalar equation for a plane ax + by + cz = d.
	 * @param a a double representing a in the above equation.
	 * @param b a double representing b in the above equation.
	 * @param c a double representing c in the above equation.
	 * @param d a double representing d in the above equation.
	 */
	Plane3(double a, double b, double c, double d);
	/**
	 * Constructs a new Plane3 with the provided glm::vec3 and direction vectors. A computation
	 * will be done to find the normal to this plane. co-linear points will cause an
	 * IllegalArgumentException to be thrown.
	 * @param point1 a first distinct glm::vec3 that is on the plane somewhere
	 * @param point2 a second distinct glm::vec3 that is on the plane somewhere
	 * @param point3 a third distinct glm::vec3 that is on the plane somewhere
	 * @throws IllegalArgumentException throws this exception if the points are co-linear
	 */
	Plane3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	/**
	 * Checks to see if a glm::vec3 is perpendicular to this Plane3. This condition is met should
	 * the provided glm::vec3 be parallel to the normal of this plane.
	 * @param other a glm::vec3 to check against this Plane3 to see if it is perpendicular
	 * @return a boolean, true if the provided glm::vec3 is perpendicular to this Plane3; otherwise false
	 */
	bool isPerpendicular(glm::vec3 other);
	/**
	 * A method to determine if the provided ILineVariant intersects with the plane.
	 * Returns false if the line variant is parallel to the plane.
	 * @param line is the ILineVariant to check for intersection
	 * @return a Boolean representing if the line variant and plane intersect
	 */
	bool does_intersect_line(ILineVariant &line);
	/**
	 * Returns true if the provided polygon intersects with the plane
	 * @param poly the polygon against which to check
	 * @return a Boolean representing if the poly intersects the plane
	 */
	bool doesIntersectPoly(Polygon3 &poly);
	/**
	 * Returns the specific point at which the plane and the provided line variant intersect.
	 * Returns NULL if no intersection occurs (as per does_intersect_plane(Ray3)).
	 * @param line - the line variant against which to check
	 * @return A glm::vec3 representing the point on the plane at which the line variant intersects.
	 * NULL if no intersection occurs.
	 */
	std::shared_ptr<glm::vec3> lineIntersectPoint(ILineVariant &line);
	/**
	 * Returns a general equation for the plane as a Vector4, in the form <a,b,c,d>
	 * for the equation aX + bY + cZ + d = 0
	 * @return a Vector4 representing the plane
	 */
	glm::vec4 getGeneralEquation();
	/**
	 * Gets the signed distance between the plane and the provided vector
	 * @param vector the glm::vec3 to calculate the distance for
	 * @return the signed distance between the point and the plane
	 */
	double distanceToPoint(glm::vec3 vector);
	glm::vec3 getNormal();
	glm::vec3 getUnitNormal();
    glm::vec3 getPointOnPlane();
	std::string toString();
private:
	/** A normal to the plane, which is therefore by definition parallel to the plane.
	 * This will be normalized on plane creation. */
	glm::vec3 normal;
	/** A point that is somewhere on the plane. Required to define the plane properly.*/
	glm::vec3 pointOnPlane;
};


#endif

#ifndef POLYGON_3
#define POLYGON_3

class Plane3;

#include <vector>
#include "plane3.h"
#include "ilinevariant.h"

/**
 * Describes a generic polygon in 3-space. Contains a list of points, and a
 * normal to the Polygon3. For provided methods to function as expected,
 * the polygon must not be degenerate (have at least three vertices), and
 * must be convex.
 * <br> <br>
 * Polygon3 prevents the Vector
 * @author      Alec Sobeck
 * @author      Matthew Robertson
 * @version     1.0
 * @since       1.0
 */
class Polygon3
{
public:
	bool isCoplanar;
	/**
	 * Creates an instance of Polygon3 from an array of Vector3. The provided Vector3[] must define a Polygon3
	 * that is coplanar and not degenerate (0, 1, or 2 vertices).
	 * @param points a Vector3[] array that defines the vertices of this Polygon3
	 * @throws IllegalArgumentException thrown if the Polygon3 being constructed would be degenerate or the
	 * polygon would not be coplanar. This is to prevent weird values appearing later that would otherwise
	 * cause problems
	 */
	Polygon3(std::vector<glm::vec3> points);
	/**
	 * Returns the normal (not a unit normal) of the polygon measured from the second point.
	 * @return A Vector3 describing the normal. This should never be null because a Polygon3 must be coplanar.
	 */
	glm::vec3 getNormal();
	/**
	 * Return the normal of the polygon measured from the second point as a unit vector.
	 * @return A Vector3 describing the normal
	 */
	glm::vec3 getUnitNormal();
	/**
	 * Calculates the area of a coplanar Polygon3. If this method fails then the area returned will be -1
	 * @return a double which is the area of this Polygon3. An area of -1 indicates insufficient vertices or a lack of coplanarity
	 */
	double area();
	/**
	 * Returns the plane on which the polygon resides, assuming it is coplanar.
	 * @return Returns the plane the polygon is on, or NULL if the  polygon is not coplanar.
	 */
	Plane3 getPlane();
	bool does_intersect_line(ILineVariant &line);
    /**
	 * Determines the point at which the ILineVariant intersects the polygon
	 * and returns the point, if one exists.
	 * @param line the ILineVariant to check
	 * @return A Vector3 if an intersection exists, null if one does not.
	 */
	std::shared_ptr<glm::vec3> line_intersect_point(ILineVariant &line);
	/**
	 * Determines if two polygons intersect
	 * @param poly the polygon against which to check
	 * @return returns true if the polygons intersect, false if they do not.
	 */
	bool does_intersect_poly(Polygon3 poly);
    /**
	 * Gets the vertices of this Polygon3.
	 * @return a Vector3[] which contains all the vertices of this Polygon3
	 */
	std::vector<glm::vec3> getVertices();
	/**
	 * Gets the number of vertices in this Polygon3. This is equivalent to a call to getVertices().length
	 * @return an int which is the total number of points in this Polygon3. This value should be greater than or equal to 3
	 */
	int getVertexCount();
	std::vector<glm::vec3> points;
	glm::vec3 normal;
protected:
	void cullNthPoint(int n);
private:
    /**
	 * Determines whether all points in the polygon lie on a single 3d plane.
	 */
	void computeIsCoplanar();
	/**
	 * Creates the Vector describing the normal of the polygon. Based on the first
	 */
	void computeNormal();
    /**
	 * Determines if an ILineVariant intersects a Triangle
	 * @param v0 the first point in the triangle
	 * @param v1 the second point in the triangle
	 * @param v2 the third point in the triangle
	 * @param coplanar whether or not the entire poly is coplanar
	 * @param line the ILineVariant to check
	 * @return true if the ILineVariant intersects the triangle, false otherwise.
	 */
	bool line_does_intersect_triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool coplanar, ILineVariant &line);
};

#endif

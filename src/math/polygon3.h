#ifndef POLYGON_3
#define POLYGON_3

class Plane3;

#include <vector>
#include "math/plane3.h"

///
/// Describes a generic polygon in 3-space. Contains a list of points, and a
/// normal to the Polygon3. For provided methods to function as expected,
/// the polygon must not be degenerate (have at least three vertices), and
/// must be convex.
/// \author      Alec Sobeck
/// \author      Matthew Robertson
///
class Polygon3
{
public:
	bool isCoplanar;
	///
	/// Creates an instance of Polygon3 from an array of Vector3. The provided Vector3[] must define a Polygon3
	/// that is coplanar and not degenerate (0, 1, or 2 vertices).
	/// throws a std::illegal_argument exception if the Polygon3 being constructed would be degenerate or the
	/// polygon would not be coplanar. This is to prevent weird values appearing later.
	/// \param points a std::vector<glm::vec3> that defines the vertices of this Polygon3
	///
	Polygon3(std::vector<glm::vec3> points);
	///
	/// Calculates the area of a coplanar Polygon3. If this method fails then the area returned will be -1
	/// \return a double which is the area of this Polygon3. An area of -1 indicates insufficient vertices or a lack of coplanarity
	///
	double area();
	///
	/// Returns the plane on which the polygon resides, assuming it is coplanar.
	/// \return Returns the plane the polygon is on, or NULL if the  polygon is not coplanar.
	///
	Plane3 getPlane() const;
	///
	/// Gets the number of vertices in this Polygon3. This is equivalent to a call to getVertices().length
	/// \return an int which is the total number of points in this Polygon3. This value should be greater than or equal to 3
	/// 
	int vertexCount() const;
	std::vector<glm::vec3> points;
	glm::vec3 normal;
protected:
	void cullNthPoint(int n);
private:
	///
	/// Determines whether all points in the polygon lie on a single 3d plane.
	/// 
	void computeIsCoplanar();
	///
	/// Creates the Vector describing the normal of the polygon. Based on the first
	/// 
	void computeNormal();
};

#endif

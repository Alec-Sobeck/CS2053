#ifndef TRIANGLE_3
#define TRIANGLE_3

#include <vector>
#include "math/plane3.h"

class Triangle3
{
public:	
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	///
	/// Creates a Triangle3 from 3 points. By definition, this triangle must be coplanar.
	///
	Triangle3(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	///
	/// Calculates the area of the triangle. If this method fails then the area returned will be -1
	///
	float area() const;
	///
	/// Returns the plane on which the polygon resides.
	///
	Plane3 getPlane() const;
	glm::vec3 normal;
private:
	///
	/// Creates the Vector describing the normal of the polygon. Based on the first
	///
	void computeNormal();
};

#endif

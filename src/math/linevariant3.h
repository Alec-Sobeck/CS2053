#ifndef ILINEVARIANT_H
#define ILINEVARIANT_H

#include "glm/vec3.hpp"
#include "plane3.h"

/// 
/// LineVariant3 describes some variant of a 3D line. This could be a Ray3, LineSegment3, or Line3.
///
class LineVariant3
{
public:
	/// 
	/// Gets the direction of the line.
	/// \return a vector that's the direction of the line
	/// 
	virtual glm::vec3 getDirection() const = 0;
	/// 
	/// Gets a point on the line.
	/// \return a point that's somewhere on the line
	/// 
	virtual glm::vec3 getPoint() const = 0;
	virtual bool intersectsPlane(const Plane3 &p) const = 0;
};


#endif

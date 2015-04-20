#ifndef ILINEVARIANT_H
#define ILINEVARIANT_H

#include "glm/vec3.hpp"

/// 
/// ILineVariant describes some variant of a line. This could be a Ray, LineSegment, or Line.
///
class ILineVariant
{
public:
	/// 
	/// Gets the direction of the line.
	/// \return a vector that's the direction of the line
	/// 
	virtual glm::vec3 getDirection() = 0;
	/// 
	/// Gets a point on the line.
	/// \return a point that's somewhere on the line
	/// 
	virtual glm::vec3 getPoint() = 0;
};


#endif

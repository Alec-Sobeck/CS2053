#pragma once

#include "glm/vec3.hpp"
#include "linevariant3.h"

///
/// Line3 represents a line in 3D space. A line has one defined point and continues on to
/// infinity in both directions using a direction vector
/// \author      Alec Sobeck
/// \author      Matthew Robertson
/// 
class Line3 : public LineVariant3
{
public:
	///
	/// A point which is part of the line in 3D space.
	///
	glm::vec3 point;
	///
	/// The direction of the line in 3D space. 
	///
	glm::vec3 direction;
	///
	/// Constructs a new Line3 instance, which requires a two glm::vec3.
	///
	Line3(glm::vec3 point, glm::vec3 direction);
	glm::vec3 getPoint() const;
	glm::vec3 getDirection() const;
	bool intersectsPlane(const Plane3 &p) const;
};



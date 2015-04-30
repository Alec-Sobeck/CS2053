#pragma once

#include <glm/vec2.hpp>

///
/// Circle2 represents a circle in 2D. A Circle2 is comprised of a Vector2, the center, and a radius.
/// \author Alec Sobeck
/// \author Matthew Robertson
///
class Circle2 
{
public:
	/// The center point of the circle. 
	glm::vec2 center;
	/// The radius of the circle. 
	float radius;
	///
	/// Constructs a new Circle2.
	/// \param center - a vec2, the center of this circle
	/// \param radius - a float, the radius of this circle
	///
	Circle2(glm::vec2 center, float radius);
};


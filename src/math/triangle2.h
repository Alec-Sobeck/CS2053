#ifndef TRIANGLE_2_H
#define TRIANGLE_2_H

#include <vector>
#include <glm/vec2.hpp>

///
/// Triangle2 represents a triangle in 2D space. A triangle must have 3 vertices.
/// \author Alec Sobeck
/// \author Matthew Robertson
///
class Triangle2 
{
public:
	std::vector<glm::vec2> points;
	///
	/// Constructs a new Triangle2. A triangle must have 3 vertices.
	/// \param points - a std::vector<glm::vec2> that will be the vertices of this Triangle2
	///
	Triangle2(std::vector<glm::vec2> points);
};



#endif

#pragma once

#include <vector>
#include <glm/vec2.hpp>

///
/// Hexagon2 represents a hexagon in 2D space. A Hexagon2 must have 6 vertices.
/// \author Alec Sobeck
/// \author Matthew Robertson
///
class Hexagon2 
{
public:
	std::vector<glm::vec2> points;

	///
	/// Constructs a new Hexagon2. A hexagon must have 6 vertices.
	/// \param points - a std::vector<glm::vec2> which is the vertices of this Hexagon2
	///
	Hexagon2(std::vector<glm::vec2> points);
};


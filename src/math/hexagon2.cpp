
#include <sstream>
#include <stdexcept>
#include "hexagon2.h"

Hexagon2::Hexagon2(std::vector<glm::vec2> points) : points(points)
{
	if (points.size() != 6)
	{
		std::stringstream ss;
		ss << "Hexagons must have 6 vertices. " << points.size() << " were given.";
		throw std::invalid_argument(ss.str());
	}
}

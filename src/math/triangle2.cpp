
#include <sstream>
#include <stdexcept>
#include "triangle2.h"

Triangle2::Triangle2(std::vector<glm::vec2> points) : points(points)
{
	if (points.size() != 3)
	{
		std::stringstream ss;
		ss << "Triangles must have 3 vertices. " << points.size() << " were given.";
		throw std::invalid_argument(ss.str());
	}
}




#include <stdexcept>
#include "math/polygon2.h"
#include "math/gamemath.h"

Polygon2::Polygon2(std::vector<glm::vec2> points) : points(points)
{
	if (points.size() <= 2)
	{
		throw std::invalid_argument("the polygon constructed with these vertices would be degenerate.");
	}
}
	
unsigned int Polygon2::vertexCount()
{
	return points.size();
}


#ifndef POLYGON_2_H
#define POLYGON_2_H

#include <vector>
#include <glm/vec2.hpp>
#include "polygonmath.h"

///
/// Polygon2 defines a polygon in 2D space with an arbitrary number of vertices. In general, this class is not very useful, but may benefit from 
/// some of the functionality in polygonmath.h nevertheless.
/// \author Alec Sobeck
/// \author Matthew Robertson
///
class Polygon2
{
public:
	std::vector<glm::vec2> points;

	///
	/// Constructs a new Polygon2 using an immutable list of PVector.
	/// \throws std::invalid_argument exception if this Polygon2 would be degenerate after being constructed.
	/// \param points a Vector2[] that will be the vertices of this Polygon2
	///
	Polygon2(std::vector<glm::vec2> points) : points(points)
	{
		if (points.size() <= 2)
		{
			throw std::invalid_argument("the polygon constructed with these vertices would be degenerate.");
		}
	}

	///
	/// Gets the number of vertices in this Polygon2. 
	/// \return an unsigned int which represents the number of vertices of this Polygon2
	///
	unsigned int vertexCount()
	{
		return points.size();
	}
};

#endif

#ifndef SEPARATING_AXIS_TEST_H
#define SEPARATING_AXIS_TEST_H

#include <vector>
#include "rectangle2.h"
#include "circle2.h"
#include "polygon2.h"
#include "triangle2.h"
#include "hexagon2.h"

namespace separatingaxistest
{
	///
	/// Tests to see if a Rectangle2 intersects with another Rectangle2.
	/// \param box1 a Rectangle2 which is one of the shapes for the intersection test
	/// \param box2 a Rectangle2 which is one of the shapes for the intersection test
	/// \return a bool - true if the rectangles intersect, otherwise false
	///
	bool intersects(const Rectangle2 &box1, const Rectangle2 &box2);
	///
	/// Tests to see if a Hexagon2 intersects with a Triangle2.
	/// \param hex a Hexagon2 which is one of the shapes for the intersection test
	/// \param tri a Triangle2 which is one of the shapes for the intersection test
	/// \return a bool; true if the polygons intersect, otherwise false
	///
	bool intersects(const Hexagon2 &hex, const Triangle2 &tri);
	///
	/// Tests to see if a Rectangle2 intersects with another Circle2.
	/// \param box a Rectangle2 which is one of the shapes for the intersection test
	/// \param circle a Circle2 which is one of the shapes for the intersection test
	/// \return a bool; true if the polygons intersect, otherwise false
	/// 
	bool intersects(const Rectangle2 &box, const Circle2 &circle);
	/// 
	/// Prepares the coordinates to vector data
	/// \return	array of vectors
	/// 
	std::vector<glm::vec2> prepareVector(Polygon2 current_box);
	///
	/// Calculates the min-max projections
	/// \return	object array of [min, min_index, max, max_index]
	/// 
	std::vector<double> getMinMax(std::vector<glm::vec2> vecs_box, glm::vec2 axis);
}

}

#endif

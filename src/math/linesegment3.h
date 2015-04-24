#ifndef LINESEGMENT3_H
#define LINESEGMENT3_H

#include "glm/vec3.hpp"
#include "linevariant3.h"

class LineSegment3 : public LineVariant3
{
public:
	/// The first Point of this line segment, of the 2 required to define it.
	/// This point is used as the tail of the glm::vec3 should this LineSegment be
	/// requested as a glm::vec3. 
	///
	glm::vec3 point1;
	///
	/// The second Point of this line segment, of the 2 required to define it.
	/// This point is used as the head of the glm::vec3 should this LineSegment be
	/// requested as a glm::vec3. 
	///
	glm::vec3 point2;
	///
	/// Constructs a new LineSegment instance, which requires two glm::vec3 to define.
	///
	LineSegment3(glm::vec3 point1, glm::vec3 point2);
	///
	/// Calculates a glm::vec3 representation of this LineSegment, whose tail will be at the first
	/// glm::vec3 and whose head will be at the second glm::vec3.
	/// \return a glm::vec3 which represents this LineSegment
	///
	glm::vec3 asVec3() const;
	///
	/// Gets the length of the LineSegment, by converting the LineSegment to a glm::vec3 and calling glm::vec3's length() method.
	/// \return a double which is the length of this LineSegment
	/// 
	double length();
	///
	/// Checks to see if two LineSegments are equal. Two segments will be equal if and only if they have the same values in each of the 
	/// corresponding elements. 
	/// \param s a LineSegment3 to compare to this LineSegment3 for equality
	/// \return a bool, true if the segments are equal or false otherwise
	///
	bool operator=(const LineSegment3 &s) const;
	///
	/// Gets the point at the middle of this LineSegment3 (The midpoint of the linesegment).
	/// \return a glm::vec3 which is at the middle of this LineSegment3
	///
	glm::vec3 midpoint();
	glm::vec3 getPoint() const;
	glm::vec3 getDirection() const;
	bool intersectsPlane(const Plane3 &p) const;
};

#endif

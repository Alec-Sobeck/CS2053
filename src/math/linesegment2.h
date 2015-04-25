#ifndef LINESEGMENT2_H
#define LINESEGMENT2_H

#include "glm/vec2.hpp"

//    TODO possible methods to implement using similar math to intersects(LineSegment2)
//        Case 1: If r × s = 0 and (q − p) × r = 0, then the two lines are collinear. If in addition, either 0 ≤ (q − p) · r ≤ r · r or 0 ≤ (p − q) · s ≤ s · s, then the two lines are overlapping.
//        Case 2: If r × s = 0 and (q − p) × r = 0, but neither 0 ≤ (q − p) · r ≤ r · r nor 0 ≤ (p − q) · s ≤ s · s, then the two lines are collinear but disjoint.
//        Case 3: If r × s = 0 and (q − p) × r ≠ 0, then the two lines are parallel and non-intersecting.
//        Case 4: Otherwise, the two line segments are not parallel but do not intersect.


class LineSegment2 
{
public:
	/// The first Point of this line segment, of the 2 required to define it.
	/// This point is used as the tail of the glm::vec2 should this LineSegment be
	/// requested as a glm::vec2. 
	///
	glm::vec2 point1;
	///
	/// The second Point of this line segment, of the 2 required to define it.
	/// This point is used as the head of the glm::vec2 should this LineSegment be
	/// requested as a glm::vec2. 
	///
	glm::vec2 point2;
	///
	/// Constructs a new LineSegment instance, which requires two glm::vec2 to define.
	///
	LineSegment2(glm::vec2 point1, glm::vec2 point2);
	///
	/// Calculates a glm::vec2 representation of this LineSegment, whose tail will be at the first
	/// glm::vec2 and whose head will be at the second glm::vec2.
	/// \return a glm::vec2 which represents this LineSegment
	///
	glm::vec2 asVec2() const;
	///
	/// Gets the length of the LineSegment, by converting the LineSegment to a glm::vec2 and calling glm::vec2's length() method.
	/// \return a double which is the length of this LineSegment
	/// 
	float length();
	///
	/// Checks to see if two LineSegments are equal. Two segments will be equal if and only if they have the same values in each of the 
	/// corresponding elements. 
	/// \param s a LineSegment2 to compare to this LineSegment2 for equality
	/// \return a bool, true if the segments are equal or false otherwise
	///
	bool operator=(const LineSegment2 &s) const;
	///
	/// Gets the point at the middle of this LineSegment2 (The midpoint of the linesegment).
	/// \return a glm::vec2 which is at the middle of this LineSegment2
	///
	glm::vec2 midpoint();
	///
	/// Equivalent to a call to extend(float) with an argument value of (-1 * length_given). Providing a
	/// negative value to this method will extend the line length. This operation will permanently modify this LineSegment.
	///	Note: The line will start going in the other direction if shortened beyond it's current length. 
	/// \param length a float which determines how far the line will be shortened if the value is positive. A negative value
	/// will determine the distance to extend the line.
	///
	void shorten(float length);
	///
	/// Extends this line by the specified length. The change in vector values with the line segment will occur to the second point
	/// in the line ("point2"). Negative values will shorten the line. This operation will permanently modify this LineSegment.
	/// Note: The line will start going in the other direction if shortened beyond it's current length.
	/// \param length - a float which determines how far the line will be extended if the value is positive. A negative value
	/// will determine the distance to shorten the line.
	///
	void extend(float length);
	///
	/// Finds a point (length) units along the line between point1 and point2, starting at point1. This may go beyond the line
	/// segment. A negative value will go in the opposite direction of the second point in the line.
	/// \param length a float which is the length to travel along the line from point1->point2
	/// \return a vec2 that is located (length) units along the line segment, starting at point1. 
	/// 
	glm::vec2 pointAlongLine(float length);
};

#endif

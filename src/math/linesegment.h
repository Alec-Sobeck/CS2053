#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <string>
#include "math/ilinevariant.h"

//TODO error checking to ensure both points are of the same dimension
//TODO test the line segment classes

/**
* LineSegment represents a line segment in nth Dimensional space. A line segment is a line that has
* 2 defined end points and will not continue forever.
* @author      Alec Sobeck
*/
class LineSegment : public ILineVariant
{
public:
	/** The first Point of this line segment, of the 2 required to define it.
 	* This point is used as the tail of the glm::vec3 should this LineSegment be
 	* requested as a glm::vec3. */
	glm::vec3 point1;
	/** The second Point of this line segment, of the 2 required to define it.
	* This point is used as the head of the glm::vec3 should this LineSegment be
	* requested as a glm::vec3. */
	glm::vec3 point2;

	/**
	 * Constructs a new LineSegment instance, which requires two glm::vec3 to define.
	 * @param point1 the first Point of the line segment, which will be used as the tail of
	 * the glm::vec3 returned by {@link #getAsglm::vec3()}
	 * @param point2 the second glm::vec3 of the line segment, which will be used as the head of
	 * the glm::vec3 returned by {@link #getAsglm::vec3()}
	 */
	LineSegment(glm::vec3 point1, glm::vec3 point2);
	/**
	 * Gets the first Point in this line segment.
	 * @return a glm::vec3, which is the first of the two in this line segment
	 */
	glm::vec3 getPoint1();
	/**
	 * Gets the second Point in this line segment.
	 * @return a glm::vec3, which is the second of the two in this line segment
	 */
	glm::vec3 getPoint2();
	/**
	 * Changes the first point of this line segment to a new Point.
	 * @param point a glm::vec3 to replace the current glm::vec3 at the start of the line segment
	 */
	void setPoint1(glm::vec3 point);
	/**
	 * Changes the second point of this line segment to a new Point.
	 * @param point a glm::vec3 to replace the current glm::vec3 at the end of the line segment
	 */
	void setPoint2(glm::vec3 point);
	/**
	 * Calculates a glm::vec3 representation of this LineSegment, whose tail will be at the first
	 * glm::vec3 and whose head will be at the second glm::vec3.
	 * @return a glm::vec3 which represents this LineSegment
	 */
	glm::vec3 getAsVec3();
	/**
	 * Returns the dimension of the points stored this LineSegment. This will fail if the dimensions are not the same.
	 * @return an int, which will be the dimension of this line segment, or -1 indicating a failure
	 */
	int getDimension();
	/**
	 * Gets the length of the LineSegment, by converting the LineSegment to a glm::vec3 and calling glm::vec3's length()
	 * method.
	 * @return a double which is the length of this LineSegment
	 */
	double length();
	/**
	 * Checks to see if two LineSegments are equal. Two segments will be equal if and only if they are of the same dimension,
	 * both non-null, and have the same values in each of the corresponding elements. For all intents and purposes
	 * LineSegments are considered equal if their respective glm::vec3 forms are equal.
	 * @param s a LineSegment to compare to this LineSegment for equality
	 * @return a boolean, true if the segments are equal or false otherwise
	 */
	bool equals(LineSegment &s);
	/**
	 * Gets the Point that is at the middle of this LineSegment (The midpoint of the line).
	 * @return a glm::vec3 which is at the middle of this LineSegment
	 */
	glm::vec3 getMidPoint();
	/**
	 * Tries to represent the LineSegment as a String in plaintext.
	 */
	std::string toString();
	/**
	 * Returns the LineSegment as a glm::vec3
	 */
	glm::vec3 getDirection();
	/**
	 * Returns the start Point (point1) of the LineSegmenmt
	 */
	glm::vec3 getPoint();
};

#endif

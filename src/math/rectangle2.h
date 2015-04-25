#ifndef RECTANGLE_2_H
#define RECTANGLE_2_H


#include <stdexcept>
#include "math/gamemath.h"
#include "intersection.h"
#include "polygonmath.h"

///
/// Rectangle2 is an extension of Polygon2 that represents a rectangle in 2D Cartesian
/// coordinates. Vertices are ordered clockwise with the first point at points[0].
/// This is considered to be the top-left corner as well.
/// \author Alec Sobeck
/// \author Matthew Robertson
///
class Rectangle2
{
public:
	std::vector<glm::vec2> points;
	///
	/// Constructs a new Rectangle2 with the specified vertices. It is assumed that the vertices are in clockwise ordering.
	/// \param points a std::vector<glm::vec2> that describes the vertices of this Rectangle2
	///
	Rectangle2(std::vector<glm::vec2> points) : points(points);
	///
	/// Constructs a new Rectangle2 using the specified values to generated vertices. The
	/// result of this calculation will be a rectangle that is axis aligned, with vertices
	/// at (x,y), (x+width,y), (x+width,y+height), (x,y+height).
	/// \param x a float which will be the x position of the newly constructed rectangle
	/// \param y a float which will be the y position of the newly constructed rectangle
	/// \param width a float which will be the width of the newly constructed rectangle.
	/// \param height a float which will be the height of the newly constructed rectangle.
	///
	Rectangle2(float x, float y, float width, float height);
	///
	/// Gets the width of this Rectangle2, which is considered to be the length of the side from points[0]->points[1]
	/// \return a float which is the width of this Rectangle, defined as the length of the side from points[0]->points[1]
	///
	float getWidth() const;
	///
	/// Gets the height of this Rectangle2, which is considered to be the length of the side from points[0]->points[3]
	/// \return a float which is the height of this Rectangle, defined as the length of the side from points[0]->points[3]
	///
	float getHeight() const;
	///
	/// Tries to extend the height of this Rectangle2 by the specified value. If changeInHeight is negative then the height will
	/// be decreased; if it is positive the height will be increased. A rectangle's height is arbitrarily decided to be the sides
	/// from points[0]->points[3] and points[1]->points[2].
	/// \param changeInHeight a float by which to change the height of this Rectangle2. A positive value will increase the height and a negative
	/// value will decrease it.
	///
	void extendHeight(float changeInHeight);
	/// 
	/// Tries to extend the width of this Rectangle2 by the specified value. If changeInWidth is negative then the width will
	/// be decreased; if it is positive the width will be increased. A rectangle's width is arbitrarily decided to be the sides
	/// from points[0]->points[1] and points[3]->points[2].
	/// \param changeInWidth - a float by which to change the width of this Rectangle2. A positive value will increase the width and a negative
	/// value will decrease it.
	/// 
	void extendWidth(double changeInWidth);
	///
	/// Gets the MidPoint of the "left side" of the Rectangle2, which is the line segment from points[3]->points[0].
	/// \return a vec2 which is the center of the line segment formed from points[3]->points[0]
	///
	glm::vec2 centerOfLeftSide() const;
	///
	/// Gets the MidPoint of the "right side" of the Rectangle, which is the line segment from points[1]->points[2].
	/// \return a vec2 which is the center of the line segment formed from points[1]->points[2]
	///
	glm::vec2 centerOfRightSide() const;
	///
	/// Gets the center of this Rectangle2. Provided the vertices actually form a rectangle the result should be correct.
	/// \return a vec2, which is the center of this Rectangle2
	///
	glm::vec2 getCenter() const;
	///
	/// Makes a very close estimate as to whether or not this Rectangle2 is in fact, geometrically, a rectangle.
	/// Due to issues in rounding floating point numbers and trigonometry being inexact this cannot ever be completely correct. The
	/// check is done by performing the following steps and will generally be correct:
	/// 1. Compare the line segments from points[0]->points[1] and points[2]->points[3] for equality. </li>
	/// 2. Compare the line segments from points[1]->points[2] and points[3]->points[0] for equality. </li>
	/// 3. Check that the inner angles are 90 degrees (PI/2 radians) </li>
	/// Success in all those checks indicates that this is most likely a rectangle, unless an extreme rounding error
	/// has occured.
	/// \return a bool, true if it's extremely likely this Rectangle2 is actually a rectangle, otherwise false
	///
	bool isProbablyRectangle() const;
	///
	/// Attempts to rotate this Rectangle2 on the center of the right side of this Rectangle2 using
	/// the provided angle. This point rotated on is considered to be the center of the line from
	/// points[1]->points[2]. This is equivalent to a call to rotateOnPoint(centerOfRightSide(), angle).
	/// \param angle - a float which describes the angle of the rotation to perform on this Rectangle2. A positive
	/// value indicates a counter-clockwise rotation and negative indicates a clockwise rotation
	///
	void rotateOnRightCenter(float angle);
	///
	/// Attempts to rotate this Rectangle2 on the center of the left side of this Rectangle2 using
	/// the provided angle. This center is considered to be the center of the line from
	/// points[3]->points[0]. This is equivalent to a call to rotateOnPoint(centerOfLeftSide(), angle).
	/// \param angle - a float which describes the angle of the rotation to perform on this Rectangle2. A positive
	/// value indicates a counter-clockwise rotation and negative indicates a clockwise rotation
	///
	void rotateOnLeftCenter(float angle);
};




#endif

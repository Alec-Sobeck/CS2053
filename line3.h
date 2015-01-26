#ifndef LINE3_H
#define LINE3_H

#include "glm/vec3.hpp"
#include "ilinevariant.h"

/**
* Line3 represents a line in 3D space. A line has one defined point and continues on to
* infinity in both directions using a direction vector
* @author      Alec Sobeck
* @author      Matthew Robertson
* @version     1.0
* @since       1.0
*/
class Line3 : public ILineVariant
{
public:
	/**
	 * Constructs a new Line3 instance, which requires a two glm::vec3.
	 * @param point
	 * @param direction
	 */
	Line3(glm::vec3 point, glm::vec3 direction);
	/**
	 * Gets a glm::vec3 which is part of this Line3.
	 * @return a glm::vec3, which is sure to be contained in this Line3
	 */
	glm::vec3 getPoint();
	/**
	* Changes the point of this line to a new glm::vec3.
	* @param point a glm::vec3 which will replace the current glm::vec3 in this Line3
	*/
	void setPoint(glm::vec3 point);
	/**
	* Gets the glm::vec3 which represents the direction of this line.
	* @return a glm::vec3 which represents the direction of this line
	*/
	glm::vec3 getDirection();
	/**
	* Sets the direction vector of this line to the provided glm::vec3.
	* @param direction a glm::vec3 which will be the new direction of this Line3
	*/
	void setDirection(glm::vec3 direction);

private:
	/** The direction of the line in 3D space. */
	glm::vec3 direction;
	/** A point which is part of the line in 3D space. */
	glm::vec3 point;
};


#endif
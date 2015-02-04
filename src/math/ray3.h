#ifndef RAY3_H
#define RAY3_H

#include <string>
#include "glm/vec3.hpp"
#include "math/ilinevariant.h"

/**
* Ray3 represents a ray in 3D space. A ray has one defined point and continues on to
* infinity in the direction of the provided glm::vec3. It is presumed that the ray begins at
* the point provided.
* @author      Alec Sobeck
* @author      Matthew Robertson
* @version     1.0
* @since       1.0
*/
class Ray3 : public ILineVariant
{
public:
	/**
	 * Constructs a new Ray3 instance, which requires a two glm::vec3.
	 * @param point
	 * @param direction
	 */
	Ray3(glm::vec3 point, glm::vec3 direction);
	/**
	* Gets a glm::vec3 which is part of this Ray3.
	* @return a glm::vec3, which is sure to be contained in this Ray3
	*/
	glm::vec3 getPoint();
	/**
	 * Changes the point of this ray to a new glm::vec3.
	 * @param point a glm::vec3 which will replace the current glm::vec3 in this Ray3
	 */
	void setPoint(glm::vec3 point);
	/**
	* Gets the glm::vec3 which represents the direction of this ray.
	* @return a glm::vec3 which represents the direction of this ray
	*/
	glm::vec3 getDirection();
	/**
	 * Sets the direction vector of this ray to the provided glm::vec3.
	 * @param direction a glm::vec3 which will be the new direction of this Ray3
	 */
	void setDirection(glm::vec3 direction);
	std::string toString();

private:
	/** The direction of the ray in 3D space. */
	glm::vec3 direction;
	/** A point which is part of the ray in 3D space. */
	glm::vec3 point;
};


#endif

#ifndef RAY3_H
#define RAY3_H

#include <string>
#include "glm/vec3.hpp"
#include "linevariant3.h"

///
/// Ray3 represents a ray in 3D space. A ray has one defined point and continues on to
/// infinity in the direction of the provided glm::vec3. It is presumed that the ray begins at
/// the point provided.
/// \author      Alec Sobeck
/// \author      Matthew Robertson
///
class Ray3 : public LineVariant3
{
public:
	///
	/// Constructs a new Ray3 instance, which requires a two glm::vec3.
	///
	Ray3(glm::vec3 point, glm::vec3 direction);
	///
	/// The direction of the ray in 3D space. 
	///
	glm::vec3 direction;
	///
	/// A point which is part of the ray in 3D space. 
	///
	glm::vec3 point;
	glm::vec3 getPoint() const;
	glm::vec3 getDirection() const;
};


#endif

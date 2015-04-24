#ifndef ENGINE_COLLISION_H
#define ENGINE_COLLISION_H

#include "glm/vec3.hpp"
#include "aabb.h"
#include "aabs.h"
#include "capsule3d.h"

bool intersects(const AABS &first, const AABS &second);
bool intersects(const AABS &first, const AABB &second);
/// 
/// Checks this AABB against an AABS for intersection
/// \return bool - true if the AABB and AABS overlap, and in all other cases false
/// 
inline bool intersects(const AABB &first, const AABS &second)
{
	return intersects(second, first);
}
bool intersectsTriangle(const AABS &first, const Polygon3 &triangle);
///
/// Compares 2 AABB against for intersection. 
/// \param other another AABB to check for overlap
/// \return bool - true if the AABB overlap, and in all other cases false
///
bool intersects(const AABB &first, const AABB &second);
/// 
/// Cheap and incomplete hittest for AABB and Capsule3D
/// 
bool brokenIntersection(const AABB &first, const Capsule3D &second);



#endif

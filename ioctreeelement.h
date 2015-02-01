#ifndef IOCTREE_ELEMENT_H
#define IOCTREE_ELEMENT_H

#include "physics/aabb.h"

/**
 * IOctreeElement Defines a couple of methods anything in an Octree should probably be
 * able to do. Currently this just means:
 * <ul>
 *  <li> {@link #getAABB()}</li>
 *  <li> {@link #onAABBCollision(AABB)}</li>
 * </ul>
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class IOctreeElement
{
public:
	/**
	 * Gets the AABB associated to this element of the Octree
	 * @return an AABB associated to this element of the octree
	 */
	virtual AABB getAABB() = 0;

	/**
	 * Defines the behaviour for a collision with another AABB.
	 * @param boundsCollidedWith another AABB that was just collided with
	 */
	virtual void onAABBCollision(AABB &boundsCollidedWith) = 0;
};



#endif // IOCTREE_ELEMENT_H

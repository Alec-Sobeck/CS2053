#ifndef MODEL_H
#define MODEL_H

#include "math/ioctreeelement.h"

class Model : public IOctreeElement
{
public:
	AABB getAABB();
	void onAABBCollision(AABB &boundsCollidedWith);
};

inline bool operator<(const Model &first, const Model &other)
{
    return false;
}


#endif

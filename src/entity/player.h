#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "glm/vec3.hpp"
#include "physics/aabb.h"
#include "physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "render/sphere.h"
#include "entity/entity.h"

/**
 * Entity is the base class for all things that exist in the world with some sort of model, and position.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class Player : public Entity
{
public:
	int ammoCount;
	int healingItemCount;
	Player(Camera camera);
	~Player();
};

#endif

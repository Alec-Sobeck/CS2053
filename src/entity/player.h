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
 */
class Player : public Entity
{
public:
	int score;
	int ammoCount;
	float invincibilityFrames;
	int healingItemCount;
	Player(Camera camera);
	~Player();
	void hurtPlayer(int amount);
	bool isDead();
	bool isInvincible();
	void update(AABB &worldBounds, float deltaTime);
};

#endif

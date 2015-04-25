#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "glm/vec3.hpp"
#include "math/physics/aabb.h"
#include "math/physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "render/sphere.h"
#include "entity/entity.h"

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
	void reset();
	bool isInvincible();
	void update(AABB &worldBounds, float deltaTime);
};

#endif

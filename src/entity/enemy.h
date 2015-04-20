#ifndef ENGINE_ENEMY_H
#define ENGINE_ENEMY_H

#include <memory>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "physics/aabb.h"
#include "physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "entity/player.h"

enum class AIState
{
	ATTACK,
	LOSING_SIGHT,
	IDLE
};

class Enemy : public Entity
{
public:
	AIState state = AIState::IDLE;
	float speedModifier;
	Enemy(std::shared_ptr<Model> model, Camera camera);
	~Enemy();
	void onGameTick(Player &player, float deltaTime, AABB &worldBounds);
	void draw(Camera* cam);
};
#endif

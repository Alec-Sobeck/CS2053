#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "math/physics/aabb.h"
#include "math/physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "entity/player.h"
#include "graphics/glstate.h"

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
	void draw(std::shared_ptr<Shader> shader, GLState &state, Camera* cam);
};
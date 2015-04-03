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

/**
* Entity is the base class for all things that exist in the world with some sort of model, and position.
*/
class Enemy : public Entity
{
public:
	AIState state = AIState::IDLE;
	float speedModifier;
	/**
	* Creates a new Entity and assigns it the provided entityID, model, and camera.
	* @param entityID an int which must uniquely identify this Entity. It is suggested that this
	* be a value generated from {@link #getNextEntityID()}
	* @param model a Model that will be used for this entity
	* @param camera a Camera that will be used for this entity
	*/
	Enemy(std::shared_ptr<Model> model, Camera camera);
	~Enemy();
	void onGameTick(Player &player, float deltaTime, AABB &worldBounds);
	void draw(Camera* cam);
};
#endif

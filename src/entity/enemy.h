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
#include "grid.h"
#include "pathfinder.h"

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
	std::shared_ptr<PathFinder> pathFinder;
	std::shared_ptr<PlannerNode> path;
	std::shared_ptr<PlannerNode> currentNode;
	glm::vec2 previousTargetPosition;
	/**
	* Creates a new Entity and assigns it the provided entityID, model, and camera.
	* @param entityID an int which must uniquely identify this Entity. It is suggested that this
	* be a value generated from {@link #getNextEntityID()}
	* @param model a Model that will be used for this entity
	* @param camera a Camera that will be used for this entity
	*/
	Enemy(std::shared_ptr<Model> model, Camera camera);
	~Enemy();
	void onGameTick(Player &player, float deltaTime, AABB &worldBounds, std::shared_ptr<Grid> worldGrid);
	void draw(Camera* cam);
	void pathfind(std::shared_ptr<Grid> worldGrid, glm::vec3, float deltaTime);
};
#endif

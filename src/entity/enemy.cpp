
#include <glbinding/gl/gl.h>
#include "math/gamemath.h"
#include "graphics/gluhelper.h"
#include "enemy.h"
#include "render/render.h"

Enemy::Enemy(std::shared_ptr<Model> model, Camera camera)
	: Entity(model, camera), speedModifier(2.0f)
{
	if (model)
	{
		this->boundingBox = model->getAABB();
	}
	else
	{
		this->boundingBox = AABB(camera.getPosition(), glm::vec3(2.5, 5, 2.5));
	}
	health = 100;
	maxHealth = 100;
}

Enemy::~Enemy()
{
}

void Enemy::onGameTick(Player &player, float deltaTime, AABB &worldBounds)
{
	// Figure out where the entity is relative to the player
	glm::vec3 toPlayer = (player.getPosition() - getPosition());
	toPlayer.y = 0;
	float distanceSquared = glm::dot(toPlayer, toPlayer);
	toPlayer = glm::normalize(toPlayer); 
	
	if (state == AIState::IDLE)
	{
		if (distanceSquared < 400)
		{
			state = AIState::ATTACK;
		}
		// Otherwise, idle and do nothing.
	}
	else if (state == AIState::ATTACK)
	{
		if (distanceSquared > 13 * 13 && distanceSquared < 25 * 25)
		{
			state = AIState::LOSING_SIGHT;
		}
		// Else chase and attack
		this->accel(toPlayer * deltaTime * speedModifier);
		camera.setRotation(glm::vec3(0, atan2(velocity.x, velocity.z), 0));
	}
	else if (state == AIState::LOSING_SIGHT)
	{
		if (distanceSquared > 25 * 25)
		{
			state = AIState::IDLE;
		}
		if (distanceSquared < 400)
		{
			state = AIState::ATTACK;
		}
		// Persue at this distance if previously chasing the player. otherwise, ignore them.
		this->accel(toPlayer * deltaTime * speedModifier);
		camera.setRotation(glm::vec3(0, atan2(velocity.x, velocity.z), 0));
	}

	this->move();
	this->boundsCheckPosition(worldBounds);
	auto pos = getPosition();

	float xHalfsize = (boundingBox.xMax - boundingBox.xMin) / 2;
	float yHalfsize = (boundingBox.yMax - boundingBox.yMin) / 2;
	float zHalfsize = (boundingBox.zMax - boundingBox.zMin) / 2;
	boundingBox = AABB(pos.x - xHalfsize, pos.y - yHalfsize, pos.z - zHalfsize, pos.x + xHalfsize, pos.y + yHalfsize, pos.z + zHalfsize);
}

void Enemy::draw(GLState &glState, Camera *cam)
{
	glState.loadIdentity();
	glState.scale(0.2f, 0.2f, 0.2f);
	glState.translate(getX(), getY(), getZ());
	glState.rotate(deg(getRotation().y), 0, 1, 0);
	glState.default3DShader->glUniformMatrix4("modelMatrix", gl::GL_FALSE, glState.model);
	model->draw(cam);
}




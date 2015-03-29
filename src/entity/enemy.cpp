
#include "enemy.h"

//
// Define methods in Entity class
//
/**
* Creates a new Entity and assigns it the provided entityID, model, and camera.
* @param entityID an int which must uniquely identify this Entity. It is suggested that this
* be a value generated from {@link #getNextEntityID()}
* @param model a Model that will be used for this entity
* @param camera a Camera that will be used for this entity
*/
Enemy::Enemy(std::shared_ptr<Model> model, Camera camera) : boundingBox(AABB(camera.getPosition(), glm::vec3(2.5, 5, 2.5))),
	entityID(getNextEntityID()), model(model), camera(camera), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f),
	health(100), maxHealth(100)
{
	if (model)
	{
		this->boundingBox = model->getAABB();
	}
}

Enemy::~Enemy()
{

}

float Enemy::getX()
{
	return camera.getX();
}

float Enemy::getY()
{
	return camera.getY();
}

float Enemy::getZ()
{
	return camera.getZ();
}

bool Enemy::affectedByGravity()
{
	return isAffectedByGravity;
}

void Enemy::setAffectedByGravity(bool isAffectedByGravity)
{
	this->isAffectedByGravity = isAffectedByGravity;
}

std::shared_ptr<Model> Enemy::getModel()
{
	return model;
}

void Enemy::setModel(std::shared_ptr<Model> newModel)
{
	this->model = newModel;
}

Camera* Enemy::getCamera()
{
	return &camera;
}

void Enemy::setCamera(Camera camera)
{
	this->camera = camera;
}

/**
* Moves the Camera the specified amount.
* @param movement a glm::vec3 that describes the movement of the Camera
*/
void Enemy::move()
{
	velocity += acceleration;

	if (abs(velocity.x) > maxMoveSpeed)
	{
		if (velocity.x > 0)
		{
			velocity = glm::vec3(maxMoveSpeed, velocity.y, velocity.z);
		}
		else
		{
			velocity = glm::vec3(-maxMoveSpeed, velocity.y, velocity.z);
		}
	}
	if (abs(velocity.y) > maxMoveSpeed)
	{
		if (velocity.y > 0)
		{
			velocity = glm::vec3(velocity.x, maxMoveSpeed, velocity.z);
		}
		else
		{
			velocity = glm::vec3(velocity.x, -maxMoveSpeed, velocity.z);
		}
	}
	if (abs(velocity.z) > maxMoveSpeed)
	{
		if (velocity.z > 0)
		{
			velocity = glm::vec3(velocity.x, velocity.y, maxMoveSpeed);
		}
		else
		{
			velocity = glm::vec3(velocity.x, velocity.y, -maxMoveSpeed);
		}
	}
	camera.setPosition(camera.getPosition() + velocity);
	boundingBox.move(velocity);
	acceleration = glm::vec3(0, 0, 0);
	velocity *= 0.6;
}

void Enemy::accel(glm::vec3 movement)
{
	acceleration += movement;
}

void Enemy::rotate(glm::vec3 amounts)
{
	camera.rotate(amounts);
}

glm::vec3 Enemy::getRotation()
{
	return camera.getRotation();
}

glm::vec3 Enemy::getPosition()
{
	return camera.getPosition();
}

AABB Enemy::getAABB()
{
	return boundingBox;
}

void Enemy::onGameTick(Entity &player, float deltaTime)
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
		if (distanceSquared > 400 && distanceSquared < 35 * 35)
		{
			state = AIState::LOSING_SIGHT;
		}
		// Else chase and attack
		float movementSpeed = 3.0f * deltaTime;
		this->accel(toPlayer * movementSpeed);
	}
	else if (state == AIState::LOSING_SIGHT)
	{
		if (distanceSquared > 35 * 35)
		{
			state = AIState::IDLE;
		}
		if (distanceSquared < 400)
		{
			state = AIState::ATTACK;
		}
		// Persue at this distance if previously chasing the player. otherwise, ignore them.
		float movementSpeed = 3.0f * deltaTime;
		this->accel(toPlayer * movementSpeed);
	}

	// Update the position
	this->move();
	auto pos = getPosition();
	boundingBox.moveTo(pos.x, pos.y, pos.z);
}

float Enemy::getHealthPercent()
{
	return health / maxHealth;
}

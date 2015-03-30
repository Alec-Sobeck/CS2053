
#include "player.h"

/**
* Creates a new Entity and assigns it the provided entityID, model, and camera.
* @param entityID an int which must uniquely identify this Entity. It is suggested that this
* be a value generated from {@link #getNextEntityID()}
* @param model a Model that will be used for this entity
* @param camera a Camera that will be used for this entity
*/
Player::Player(Camera camera) : Entity(std::shared_ptr<Model>(nullptr), camera), ammoCount(500), healingItemCount(3), invincibilityFrames(0)
{
}

Player::~Player()
{
}

void Player::hurtPlayer(int amount)
{
	if (invincibilityFrames <= 0)
	{
		this->health -= amount;
		invincibilityFrames = 1.4f;
	}
}

bool Player::isInvincible()
{
	return invincibilityFrames > 0.0f;
}

bool Player::isDead()
{
	return health <= 0;
}

void Player::update(AABB &worldBounds, float deltaTime)
{
	move();
	boundsCheckPosition(worldBounds);
	invincibilityFrames -= deltaTime;
	if (health < 0)
		health = 0;
	if (health > maxHealth)
		health = maxHealth;
}
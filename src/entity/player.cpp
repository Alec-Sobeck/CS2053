
#include "player.h"

Player::Player(Camera camera) 
	: Entity(std::shared_ptr<Model>(nullptr), camera), ammoCount(500), healingItemCount(3), invincibilityFrames(0), score(0)
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

void Player::reset()
{
	this->health = maxHealth;
	this->healingItemCount = 3;
	this->invincibilityFrames = 0;
	this->score = 0;
	this->ammoCount = 500;
	camera.setPosition(glm::vec3(30, 0, 30));
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
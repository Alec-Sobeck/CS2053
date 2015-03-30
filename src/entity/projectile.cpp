
#include "projectile.h"

/**
 * Creates a new Entity and assigns it the provided entityID, model, and camera.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 * @param model a Model that will be used for this entity
 * @param camera a Camera that will be used for this entity
 */
Projectile::Projectile(Camera camera, float size) : Entity(std::shared_ptr<Model>(nullptr), camera), size(size), boundingSphere(AABS(camera.getPosition(), size)),
	sphere(Sphere(size, 12, 24))
{
	maxMoveSpeed = (10000.0f);
}

Projectile::~Projectile()
{
}

void Projectile::onGameTick(float deltaTime)
{
	move(deltaTime);
	auto pos = getPosition();
	this->boundingSphere.moveTo(pos.x, pos.y, pos.z);
}

void Projectile::draw()
{
	auto pos = getPosition();
	sphere.draw(pos.x, pos.y, pos.z);
}

void Projectile::move(float deltaTime)
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

	camera.move(velocity * deltaTime);
}
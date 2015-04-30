
#include "projectile.h"

Projectile::Projectile(Camera camera, float size, GLState &glState) 
	: Entity(std::shared_ptr<Model>(nullptr), camera), size(size), boundingSphere(AABS(camera.getPosition(), size)), sphere(Sphere(glState, size, 12, 24))
{
	maxMoveSpeed = 10000.0f;
}

Projectile::~Projectile()
{
}

void Projectile::onGameTick(float deltaTime)
{
	previousPosition = getPosition();
	move(deltaTime);
	auto pos = getPosition();
	this->boundingSphere.moveTo(pos.x, pos.y, pos.z);
}

void Projectile::draw(GLState &glState, std::shared_ptr<Texture> texture)
{
	auto pos = getPosition();
	sphere.draw(glState, texture, pos.x, pos.y, pos.z);
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

LineSegment3 Projectile::getMovement()
{
	return LineSegment3(previousPosition, getPosition());
}
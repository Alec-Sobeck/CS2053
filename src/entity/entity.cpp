
#include "entity.h"

//
// Define functions in entity.h
//
int getNextEntityID()
{
    // TODO -- make this function threadsafe
    static int nextEntityID = 0;
    return nextEntityID++;
}

//
// Define methods in Entity class
//
Entity::Entity() : boundingBox(AABB(glm::vec3(0, 0, 0), glm::vec3(2.5, 2.5, 2.5))), entityID(getNextEntityID()),
    model(std::shared_ptr<Model>(nullptr)), camera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))),
    velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f), isAffectedByGravity(false),
	isNoClipActive(false), health(100), maxHealth(100)
{
}

/**
 * Creates a new Entity and assigns it the provided entityID, model, and camera.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 * @param model a Model that will be used for this entity
 * @param camera a Camera that will be used for this entity
 */
Entity::Entity(std::shared_ptr<Model> model, Camera camera) : boundingBox(AABB(camera.getPosition(), glm::vec3(2.5, 5, 2.5))),
    entityID(getEntityID()), model(model), camera(camera), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f),
	health(100), maxHealth(100)
{
}

Entity::~Entity()
{

}

float Entity::getX()
{
    return camera.getX();
}

float Entity::getY()
{
    return camera.getY();
}

float Entity::getZ()
{
    return camera.getZ();
}

bool Entity::noClipActive()
{
    return isNoClipActive;
}

void Entity::setNoClipActive(bool isNoClipActive)
{
    this->isNoClipActive = isNoClipActive;
}

bool Entity::affectedByGravity()
{
    return isAffectedByGravity;
}

void Entity::setAffectedByGravity(bool isAffectedByGravity)
{
    this->isAffectedByGravity = isAffectedByGravity;
}

int Entity::getEntityID()
{
    return entityID;
}

std::shared_ptr<Model> Entity::getModel()
{
    return model;
}

void Entity::setModel(std::shared_ptr<Model> newModel)
{
    this->model = newModel;
}

Camera* Entity::getCamera()
{
    return &camera;
}

void Entity::setCamera(Camera camera)
{
    this->camera = camera;
}

/**
 * Moves the Camera the specified amount.
 * @param movement a glm::vec3 that describes the movement of the Camera
 */
 void Entity::move()
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
    acceleration = glm::vec3(0,0,0);
    velocity *= 0.6;
}

void Entity::accel(glm::vec3 movement)
{
    acceleration += movement;
}

void Entity::rotate(glm::vec3 amounts)
{
    camera.rotate(amounts);
}

glm::vec3 Entity::getRotation()
{
    return camera.getRotation();
}

glm::vec3 Entity::getPosition()
{
    return camera.getPosition();
}

AABB Entity::getAABB()
{
    return boundingBox;
}

float Entity::getHealthPercent()
{
	return health / maxHealth;
}

void Entity::boundsCheckPosition(AABB &worldBounds)
{
	AABB &bounds = this->boundingBox;

	float xHalfsize = (bounds.xMax - bounds.xMin) / 2;
	float yHalfsize = (bounds.yMax - bounds.yMin) / 2;
	float zHalfsize = (bounds.zMax - bounds.zMin) / 2;

	float x = getX();
	float y = getY();
	float z = getZ();

	if (x - xHalfsize < worldBounds.xMin)
	{
		x = xHalfsize + worldBounds.xMin;
	}
	if (x + xHalfsize > worldBounds.xMax)
	{
		x = worldBounds.xMax - xHalfsize;
	}
	if (y - yHalfsize < worldBounds.yMin)
	{
		y = worldBounds.yMin + yHalfsize;
	}
	if (y + yHalfsize > worldBounds.yMax)
	{
		y = worldBounds.yMax - yHalfsize;
	}
	if (z - zHalfsize < worldBounds.zMin)
	{
		z = zHalfsize + worldBounds.zMin;
	}
	if (z + zHalfsize > worldBounds.zMax)
	{
		z = worldBounds.zMax - zHalfsize;
	}
	camera.setPosition(glm::vec3(x, y, z));
}

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
    camera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f),
    isAffectedByGravity(false), isNoClipActive(false)
{
}

/**
 * Constructs a new Entity, assigning it the entityID provided and a camera with position
 * and rotation of 0.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 */
Entity::Entity(int entityID) : boundingBox(AABB(glm::vec3(0, 0, 0), glm::vec3(2.5, 2.5, 2.5))), entityID(entityID),
    camera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f),
    isAffectedByGravity(false), isNoClipActive(false)
{
}

/**
 * Creates a new Entity and assigns it the provided entityID, model, and camera.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 * @param model a Model that will be used for this entity
 * @param camera a Camera that will be used for this entity
 */
Entity::Entity(int entityID, Model model, Camera camera) : boundingBox(AABB(camera.getPosition(), glm::vec3(2.5, 5, 2.5))),
    entityID(entityID), model(model), camera(camera), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(0.5f)
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

Model Entity::getModel()
{
    return model;
}

void Entity::setModel(Model &newModel)
{
    this->model = newModel;
}

Camera Entity::getCamera()
{
    return camera;
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

void Entity::onGameTick()
{
}

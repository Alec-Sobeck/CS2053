
#include "projectile.h"

Projectile::Projectile() : size(10), boundingSphere(AABS(0, 0, 0, 0)), entityID(getEntityID()),
    camera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))), velocity(glm::vec3(0, 0, 0)), 
	acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(10000.0f), isAffectedByGravity(true), sphere(Sphere(size, 12, 24))
{
}

/**
 * Constructs a new Entity, assigning it the entityID provided and a camera with position
 * and rotation of 0.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 */
Projectile::Projectile(int entityID) : size(10), boundingSphere(AABS(0, 0, 0, 0)), entityID(entityID),
    camera(Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(10000.0f),
	isAffectedByGravity(false), sphere(Sphere(size, 12, 24))
{
}

/**
 * Creates a new Entity and assigns it the provided entityID, model, and camera.
 * @param entityID an int which must uniquely identify this Entity. It is suggested that this
 * be a value generated from {@link #getNextEntityID()}
 * @param model a Model that will be used for this entity
 * @param camera a Camera that will be used for this entity
 */
Projectile::Projectile(int entityID, Camera camera, float size) : size(size), boundingSphere(AABS(camera.getPosition(), size)),
	entityID(entityID), camera(camera), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(10000.0f), sphere(Sphere(size, 12, 24))
	
{
}

/**
* Creates a new Entity and assigns it the provided entityID, model, and camera.
* @param entityID an int which must uniquely identify this Entity. It is suggested that this
* be a value generated from {@link #getNextEntityID()}
* @param model a Model that will be used for this entity
* @param camera a Camera that will be used for this entity
*/
Projectile::Projectile(Camera camera, float size) : size(size), boundingSphere(AABS(camera.getPosition(), size)),
	entityID(getEntityID()), camera(camera), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), maxMoveSpeed(10000.0f), sphere(Sphere(size, 12, 24))
{
}

Projectile::~Projectile()
{

}

float Projectile::getX()
{
    return camera.getX();
}

float Projectile::getY()
{
    return camera.getY();
}

float Projectile::getZ()
{
    return camera.getZ();
}

bool Projectile::affectedByGravity()
{
    return isAffectedByGravity;
}

void Projectile::setAffectedByGravity(bool isAffectedByGravity)
{
    this->isAffectedByGravity = isAffectedByGravity;
}

int Projectile::getEntityID()
{
    return entityID;
}

Camera* Projectile::getCamera()
{
    return &camera;
}

void Projectile::setCamera(Camera camera)
{
    this->camera = camera;
}

/**
 * Moves the Camera the specified amount.
 * @param movement a glm::vec3 that describes the movement of the Camera
 */
void Projectile::move(float deltaTime)
 {
    velocity += acceleration * deltaTime;

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
    //acceleration = glm::vec3(0, -9.8f, 0);
    //velocity *= 0.6;
}

void Projectile::accel(glm::vec3 movement)
{
    acceleration += movement;
}

void Projectile::rotate(glm::vec3 amounts)
{
    camera.rotate(amounts);
}

glm::vec3 Projectile::getRotation()
{
    return camera.getRotation();
}

glm::vec3 Projectile::getPosition()
{
    return camera.getPosition();
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
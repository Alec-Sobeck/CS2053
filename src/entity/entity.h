#pragma once

#include <memory>
#include "glm/vec3.hpp"
#include "math/physics/aabb.h"
#include "math/physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"

///
/// Gets the next entityID that has not been used. @TODO -- make this threadsafe again
/// \return an int which will uniquely identify an entity
///
int getNextEntityID();

///
/// Entity is the base class for all things that exist in the world with some sort of model, and position.
///
class Entity
{
public:
	AABB boundingBox;
    /// An integer which uniquely identifies this entity in the world. Generated by getNextEntityID() 
	const int entityID;
	float health;
	float maxHealth;
    ///
	/// Constructs a new Entity, assigning it the next valid entityID available and a camera with position and rotation of 0.
	///
    Entity();
	///
	/// Creates a new Entity and assigns it the provided entityID, model, and camera.
	/// \param model a Model that will be used for this entity
	/// \param camera a Camera that will be used for this entity
	///
    Entity(std::shared_ptr<Model> model, Camera camera);
    virtual ~Entity();
    float getX();
	float getY();
	float getZ();
	int getEntityID();
    bool noClipActive();
    void setNoClipActive(bool isNoClipActive);
	bool affectedByGravity();
	void setAffectedByGravity(bool isAffectedByGravity);
	std::shared_ptr<Model> getModel();
	AABB getAABB();
    void setModel(std::shared_ptr<Model> newModel);
    Camera *getCamera();
	void setCamera(Camera camera);
	void boundsCheckPosition(AABB &worldBounds);
    void move();
	void accel(glm::vec3 movement);
	void rotate(glm::vec3 rotation);
    glm::vec3 getRotation();
    glm::vec3 getPosition();
	float getHealthPercent();
	void hurt(int amount);
	bool isDead();
protected:
	/// A model somehow associated to this entity. 
    std::shared_ptr<Model> model;
	/// A camera which controls the movement of this entity.
    Camera camera;
    glm::vec3 velocity;
	glm::vec3 acceleration;
	double maxMoveSpeed;
	/// true if the entity should follow the laws of gravity, or false if gravity ignores them. 
	bool isAffectedByGravity;
	/// true if the entity is in noclip mode, allowing mostly free movement within the scene. Generally,
	/// it makes sense to have this set to false (except for debug purposes). 
	bool isNoClipActive;
};



#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>
#include "glm/vec3.hpp"
#include "physics/aabb.h"
#include "physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "render/sphere.h"
#include "entity.h"
#include "math/linesegment3.h"

/**
 * Entity is the base class for all things that exist in the world with some sort of model, and position.
 */
class Projectile : public Entity
{
public:
	int size;
	AABS boundingSphere;
	glm::vec3 previousPosition;
	/**
	 * Creates a new Entity and assigns it the provided entityID, model, and camera.
     * @param entityID an int which must uniquely identify this Entity. It is suggested that this
     * be a value generated from {@link #getNextEntityID()}
	 * @param model a Model that will be used for this entity
	 * @param camera a Camera that will be used for this entity
	 */
	Projectile(Camera camera, float size = 0);
	~Projectile();
	void draw();
	void onGameTick(float deltaTime);
	void move(float deltaTime);
	LineSegment3 getMovement();

protected:
	Sphere sphere;
};

inline bool operator==(const Projectile& one, const Projectile& two)
{
	return false;
}

#endif

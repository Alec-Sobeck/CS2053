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

class Projectile : public Entity
{
public:
	int size;
	AABS boundingSphere;
	glm::vec3 previousPosition;
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

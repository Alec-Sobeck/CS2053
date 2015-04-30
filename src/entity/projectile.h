#pragma once

#include <memory>
#include "glm/vec3.hpp"
#include "math/physics/aabb.h"
#include "math/physics/aabs.h"
#include "graphics/camera.h"
#include "graphics/model.h"
#include "render/sphere.h"
#include "entity.h"
#include "graphics/glstate.h"
#include "math/linesegment3.h"

class Projectile : public Entity
{
public:
	int size;
	AABS boundingSphere;
	glm::vec3 previousPosition;
	Projectile(Camera camera, float size, GLState &glState);
	~Projectile();
	void draw(GLState &glState, std::shared_ptr<Texture> texture);
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


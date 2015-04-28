#ifndef GL_STATE_H
#define GL_STATE_H

#include "math/gamemath.h"
#include "camera.h"

class GLState
{
public:
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;

	/// Loads the identity matrix into the model matrix
	void loadIdentity();
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void update(Camera* camera);
};

#endif

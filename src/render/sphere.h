#pragma once

#include <vector>
#include <memory>
#include <glbinding/gl/gl.h>
#include "vao.h"
#include "texture.h"
#include "graphics/glstate.h"

class Sphere
{
protected:
	std::shared_ptr<TexturedNormalColouredIndexedVAO> vao;

public:
	Sphere(GLState &glState, float radius, unsigned int rings, unsigned int sectors);
	void draw(GLState &state, std::shared_ptr<Texture> tex, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z);
};





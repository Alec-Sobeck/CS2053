#pragma once

#include <string>
#include <memory>
#include "render/texture.h"
#include "gameloop.h"
#include "render/vao.h"
#include "shaders/shader.h"
#include "graphics/glstate.h"
#include "utils/utilities.h"

///
/// ComponentBase defines an abstract base class for all user interface components. 
///
class ComponentBase
{
public:
	std::shared_ptr<Texture> renderTexture;
	float width;
	float height;
	float x;
	float y;

	ComponentBase(std::shared_ptr<Texture> t, float x, float y, float width, float height);
	virtual void draw(GLState &glState) = 0;
	virtual void update(GLState &glState, MouseManager *manager) = 0;
	void rebuildVAO();
	void drawBackground(GLState &glState);
};


#pragma once

#include <string>
#include "componentbase.h"
#include "render/vao.h"

class Slider : public ComponentBase
{
private:
	const float BAR_WIDTH = 10;

public:
	float value;	
	Slider(std::shared_ptr<Texture> tex, float x, float y, float width, float height);
	virtual void draw(GLState &glState) override;
	virtual void update(GLState &glState, MouseManager *manager) override;
};


#pragma once

#include <string>
#include "componentbase.h"

class Logo : public ComponentBase
{
public:
	Logo(std::shared_ptr<Texture> tex, float x, float y, float width, float height);
	virtual void draw(GLState &glState) override;	
	virtual void update(GLState &glState, const MouseManager &manager) override;
};



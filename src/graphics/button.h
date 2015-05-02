#pragma once

#include <string>
#include "componentbase.h"

class Button : public ComponentBase
{
public:
	Button(std::shared_ptr<Texture> tex, double x, double y, double width, double height);
	virtual void draw(GLState &glState) override;
	virtual void update(GLState &glState, MouseManager *manager) override;
};


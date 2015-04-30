#pragma once

#include <string>
#include "componentbase.h"
#include "render/vao.h"

class Slider : public ComponentBase
{
private:
	std::shared_ptr<ColouredVAO> vao;

public:
	float value;	
	Slider(std::shared_ptr<Texture> tex, float x, float y, float width, float height);
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
	void rebuildVAO();
};


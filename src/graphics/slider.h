#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include <string>
#include "componentbase.h"

class Slider : public ComponentBase
{
public:
	float value;	
	Slider(std::shared_ptr<Texture> tex, float x, float y, float width, float height);
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
};


#endif

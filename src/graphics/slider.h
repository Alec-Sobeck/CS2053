#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include <string>
#include "componentbase.h"

class Slider : public ComponentBase
{
public:
	float value;	
	Slider(std::shared_ptr<Texture> tex, double x, double y, double width, double height);
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
};


#endif

#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <string>
#include "componentbase.h"

class Button : public ComponentBase
{
public:
	Button(std::shared_ptr<Texture> tex, double x, double y, double width, double height);
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
};


#endif

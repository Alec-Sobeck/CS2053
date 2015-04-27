#ifndef GUI_LOGO_H
#define GUI_LOGO_H

#include <string>
#include "componentbase.h"

class Logo : public ComponentBase
{
public:
	Logo(std::shared_ptr<Texture> tex, float x, float y, float width, float height);
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
};


#endif


#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "slider.h"
#include "math/gamemath.h"
#include "graphics/rendersettingshelper.h"


Slider::Slider(std::shared_ptr<Texture> tex, float x, float y, float width, float height)
	: ComponentBase(tex, (getViewportWidth() / 2) - (width / 2.0f), y, width, height), value(0.5f)
{
}

void Slider::draw(GLState &glState)
{
	x = (getViewportWidth() / 2) - (width / 2.0f); 
	drawBackground(glState);
	glState.draw2DColouredQuad(utils::Colour(1.0f, 1.0f, 1.0f, 1.0f), x + (width * value), y, BAR_WIDTH, height);
}

void Slider::update(GLState &glState, MouseManager *manager)
{
	if (manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		if (glState.inBounds(manager->x, manager->y, x, y, width, height))
		{
			this->value = clamp((manager->x - this->x) / this->width);
		}
	}
}

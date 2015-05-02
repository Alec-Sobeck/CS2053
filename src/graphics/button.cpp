
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "button.h"


Button::Button(std::shared_ptr<Texture> tex, double x, double y, double width, double height)
	: ComponentBase(tex, x, y, width, height)
{
}

void Button::draw(GLState &glState)
{
	drawBackground(glState);
}

void Button::update(GLState &glState, MouseManager *manager)
{
}

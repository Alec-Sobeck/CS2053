
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "button.h"


Button::Button(std::shared_ptr<Texture> tex, double x, double y, double width, double height) : ComponentBase(tex, x, y, width, height)
{

}

/**
* Draws the button, and fixes the position if the screen has been resized
*/
void Button::draw()
{
	drawBackground();
}

void Button::update()
{
}

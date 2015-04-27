
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "logo.h"


Logo::Logo(std::shared_ptr<Texture> tex, float x, float y, float width, float height)
	: ComponentBase(tex, x, y, width, height)
{
}

void Logo::draw()
{
	drawBackground();
}

void Logo::update(MouseManager *manager)
{
}

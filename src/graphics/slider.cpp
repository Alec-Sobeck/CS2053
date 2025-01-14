
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "slider.h"
#include "math/gamemath.h"


Slider::Slider(std::shared_ptr<Texture> tex, double x, double y, double width, double height) : ComponentBase(tex, x, y, width, height), value(0.5f)
{

}

/**
* Draws the button, and fixes the position if the screen has been resized
*/
void Slider::draw()
{
	using namespace gl;
	drawBackground();
	
	//The "slide bar"
	const float BAR_WIDTH = 10;
	double barPosition = (this->value - BAR_WIDTH < 0) ? 0 : (this->value - BAR_WIDTH > 0.95) ? 0.95 : (this->value - (BAR_WIDTH));
	float x1 = x + (width * value);
	glDisable(GL_TEXTURE_2D);
	glColor4d(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glVertex3d(x1, y + height, 0);
		glTexCoord2f(0, 1);
		glVertex3d(x1 + BAR_WIDTH, y + height, 0);
		glTexCoord2f(1, 1);
		glVertex3d(x1 + BAR_WIDTH, y, 0);
		glTexCoord2f(1, 0);
		glVertex3d(x1, y, 0);
		glTexCoord2f(0, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void Slider::update(MouseManager *manager)
{
	if (manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		if (inBounds(manager->x, manager->y))
		{
			this->value = clamp((manager->x - this->x) / this->width);
		}
	}
}

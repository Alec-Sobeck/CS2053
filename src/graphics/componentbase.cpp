
#include <glbinding/gl/gl.h>
#include <vector>
#include "windowhelper.h"
#include "render/glfont.h"
#include "utils/colour.h"
#include "graphics/rendersettingshelper.h"
#include "componentbase.h"

ComponentBase::ComponentBase(std::shared_ptr<Texture> t, double x, double y, double width, double height) 
	: renderTexture(t), x(x), y(y), width(width), height(height)
{
}

bool ComponentBase::inBounds(int mouseX, int mouseY)
{
	float y = this->y;
	if (y < 0)
	{
		y = getWindowHeight() + y;
	}

	return (mouseX > x &&
		mouseX < x + width &&
		mouseY > y &&
		mouseY < y + height);
}

void ComponentBase::drawBackground()
{
	using namespace gl;
	float y = this->y;
	if (y < 0)
	{
		y = getWindowHeight() + y;
	}

	//Draw the background texture if there is one. 
	glEnable(GL_TEXTURE_2D);
	renderTexture->bind();
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glVertex3d(x, y + height, 0);
		glTexCoord2f(1, 0);
		glVertex3d(x + width, y + height, 0);
		glTexCoord2f(1, 1);
		glVertex3d(x + width, y, 0);
		glTexCoord2f(0, 1);
		glVertex3d(x, y, 0);
		glTexCoord2f(0, 0);
	glEnd();
}
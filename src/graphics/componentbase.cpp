
#include <glbinding/gl/gl.h>
#include <vector>
#include "windowhelper.h"
#include "render/glfont.h"
#include "utils/colour.h"
#include "graphics/rendersettingshelper.h"
#include "componentbase.h"


ComponentBase::ComponentBase(std::shared_ptr<Texture> t, double x, double y, double width, double height) : renderTexture(t), x(x), y(y), width(width), height(height)
{
}

/**
* Gets whether or not a point is inside this LWJGLComponent, including whether or not it is inside the border.
* @param x the x value of the point to compare
* @param y the y value of the point to compare
* @return a boolean indicating whether the point is in bounds of this component
*/
bool ComponentBase::inBounds(int mouseX, int mouseY)
{
	return (mouseX > x &&
		mouseX < x + width &&
		mouseY > y &&
		mouseY < y + height);
}

/**
* Draws some sort of background which is based on the background color, border color, and border style.
* This may be overridden to do something different in each component.
* @param parentOffsetX a double which is how far the parent component offsets this component along the x axis
* @param parentOffsetY a double which is how far the parent component offsets this component along the y axis
*/
void ComponentBase::drawBackground()
{
	using namespace gl;
	//Draw the background texture if there is one. 

	renderTexture->bind();
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3d(x, y + height, 0);
	glTexCoord2f(0, 1);
	glVertex3d(x + width, y + height, 0);
	glTexCoord2f(1, 1);
	glVertex3d(x + width, y, 0);
	glTexCoord2f(1, 0);
	glVertex3d(x, y, 0);
	glTexCoord2f(0, 0);
	glEnd();
}
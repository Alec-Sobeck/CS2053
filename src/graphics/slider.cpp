
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include "slider.h"
#include "math/gamemath.h"
#include "graphics/rendersettingshelper.h"


Slider::Slider(std::shared_ptr<Texture> tex, float x, float y, float width, float height)
	: ComponentBase(tex, (getViewportWidth() / 2) - (width / 2.0f), y, width, height), value(0.5f)
{
}

void Slider::draw()
{
	using namespace gl;
	x = (getViewportWidth() / 2) - (width / 2.0f); 
	drawBackground();

	rebuildVAO();

	//Draw the background texture if there is one. 
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	auto shader = getDefault2DColourShader();
	shader->bindShader();
	vao->draw();
}

void Slider::rebuildVAO()
{
	//The "slide bar"
	const float BAR_WIDTH = 10;
	float barX = x + (width * value);

	float x = getAdjustedX(barX);
	float y = getAdjustedY(this->y);
	float width = getAdjustedWidth(BAR_WIDTH);
	float height = getAdjustedHeight(this->height);

	float colours[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 1.0f,
	};
	float vertices[] = {
		x, y + height, 0.0f,
		x + width, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y, 0.0f
	};

	auto defaultShader = getDefault2DColourShader();
	vao = std::shared_ptr<ColouredVAO>(new ColouredVAO(
		defaultShader->programID, 6, vertices, sizeof(vertices), colours, sizeof(colours)
	));
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

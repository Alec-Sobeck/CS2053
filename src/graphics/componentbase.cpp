
#include <glbinding/gl/gl.h>
#include <vector>
#include "windowhelper.h"
#include "render/glfont.h"
#include "utils/colour.h"
#include "graphics/rendersettingshelper.h"
#include "componentbase.h"
#include "utils/fileutils.h"
#include "math/gamemath.h"

std::shared_ptr<Shader> getDefault2DTextureShader()
{
	static std::shared_ptr<Shader> val = nullptr;
	if (!val)
	{
		std::string vert = buildPath("res/shaders/2d_textured_coloured_triangles.vert");
		std::string frag = buildPath("res/shaders/2d_textured_coloured_triangles.frag");
		val = createShader(&vert, &frag);
	}
	return val;
}

std::shared_ptr<Shader> getDefault2DColourShader()
{
	static std::shared_ptr<Shader> val = nullptr;
	if (!val)
	{
		std::string vert = buildPath("res/shaders/2d_coloured_triangles.vert");
		std::string frag = buildPath("res/shaders/2d_coloured_triangles.frag");
		val = createShader(&vert, &frag);
	}
	return val;
}

ComponentBase::ComponentBase(std::shared_ptr<Texture> t, float x, float y, float width, float height)
	: renderTexture(t), x(x), y(y), width(width), height(height), previousScreenWidth(getWindowWidth()), previousScreenHeight(getWindowHeight())
{
	rebuildVAO();
}

bool ComponentBase::inBounds(int mouseX, int mouseY)
{
	// Scale mouseX, mouseY to floats on [-1, 1]
	float f_mouseX = getAdjustedX(static_cast<float>(mouseX - getViewportX()));
	float f_mouseY = getAdjustedY(static_cast<float>(mouseY - getViewportY()));
	// Scale bounding values to [-1, 1]
	float x = getAdjustedX(this->x);
	float y = getAdjustedY(this->y);
	float width = getAdjustedWidth(this->width);
	float height = getAdjustedHeight(this->height);
	
	/*
	static int counter = 0;
	counter++;
	if (counter >= 3000)
	{
		counter -= 3000;
		std::cout << "Viewport: " << getViewportX() << " " << getViewportY() << " " << getViewportWidth() << " " << getViewportHeight() << std::endl;
		std::cout << "Mouse: " << mouseX << ", " << mouseY << " scaled: " << f_mouseX << "," << f_mouseY << std::endl;
		std::cout << "Bounds: " << x << " " << y << " " << width << " " << height << std::endl;
	}
	*/

	return (between(x, x + width, f_mouseX) && between(y, y + height, f_mouseY));
}

void ComponentBase::rebuildVAO()
{
	float x = getAdjustedX(this->x);
	float y = getAdjustedY(this->y);
	float width = getAdjustedWidth(this->width);
	float height = getAdjustedHeight(this->height);

	float colours[] = {
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 
	};
	float textures[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	float vertices[] = {
		x,		   y + height, 0.0f,
		x + width, y + height, 0.0f,
		x + width, y,		   0.0f,
		x,		   y + height, 0.0f,
		x + width, y,		   0.0f,
		x,		   y,		   0.0f
	};

	auto defaultShader = getDefault2DTextureShader();
	vao = std::shared_ptr<TexturedColouredVAO>(new TexturedColouredVAO(
		defaultShader->programID, 6, vertices, sizeof(vertices), colours, sizeof(colours), textures, sizeof(textures)
	));
}

float ComponentBase::getAdjustedX(float val)
{
	return (val / getViewportWidth()) * 2.0f - 1.0f;
}

float ComponentBase::getAdjustedY(float val)
{
	float y = val;
	if (y < 0)
	{
		y = getViewportHeight() + y;
	}
	return -1.0f * ((y / getViewportHeight()) * 2.0f - 1.0f);
}

float ComponentBase::getAdjustedWidth(float val)
{
	return (val / getViewportWidth()) * 2.0f;

}

float ComponentBase::getAdjustedHeight(float val)
{
	return -1.0f * ((val / getViewportHeight()) * 2.0f);
}

void ComponentBase::drawBackground()
{
	using namespace gl;
	if (previousScreenWidth != getWindowWidth() || previousScreenHeight != getWindowHeight())
	{
		previousScreenWidth = getWindowWidth();
		previousScreenHeight = getWindowHeight();
		rebuildVAO();
	}

	//Draw the background texture if there is one. 
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	auto shader = getDefault2DTextureShader();
	shader->bindShader();
	renderTexture->bind();
	shader->glUniform1("texture1", 0);
	vao->draw();
}
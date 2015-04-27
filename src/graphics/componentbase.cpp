
#include <glbinding/gl/gl.h>
#include <vector>
#include "windowhelper.h"
#include "render/glfont.h"
#include "utils/colour.h"
#include "graphics/rendersettingshelper.h"
#include "componentbase.h"
#include "utils/fileutils.h"
#include "math/gamemath.h"



std::shared_ptr<Shader> getDefault2DShader()
{
	static std::shared_ptr<Shader> val = nullptr;
	if (!val)
	{
		std::string vert = buildPath("res/shaders/basic_texture_150.vert");
		std::string frag = buildPath("res/shaders/basic_texture_150.frag");
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
	float y = this->y;
	if (y < 0)
	{
		y = getViewportHeight() + y;
	}

	// Scale mouseX, mouseY to floats on [-1, 1]
	float f_mouseX = (static_cast<float>(mouseX - getViewportX()) / getViewportWidth()) * 2.0f - 1.0f;
	float f_mouseY = -1.0f * (static_cast<float>(mouseY - getViewportY()) / getViewportHeight());

	// Scale bounding values to [-1, 1]
	int vwidth = getViewportWidth();
	int vheight = getViewportHeight();
	float x = (this->x / vwidth) * 2.0f - 1.0f;
	y = -1.0f * ((y / vheight) * 2.0f - 1.0f);
	float width = (this->width / vwidth) * 2.0f;
	float height = -1.0f * ((this->height / vheight) * 2.0f);

	static int counter = 0;
	counter++;
	if (counter >= 3000)
	{
		counter -= 3000;
		std::cout << "Viewport: " << getViewportX() << " " << getViewportY() << " " << getViewportWidth() << " " << getViewportHeight() << std::endl;

		std::cout << "Mouse: " << mouseX << ", " << mouseY << " scaled: " << f_mouseX << "," << f_mouseY << std::endl;

		std::cout << "Bounds: " << x << " " << y << " " << width << " " << height << std::endl;
	}


	return (between(x, x + width, f_mouseX) &&
		between(y, y + height, f_mouseY));
}

void ComponentBase::rebuildVAO()
{
	int vwidth = getViewportWidth();
	int vheight = getViewportHeight();

	float y = this->y;
	if (y < 0)
	{
		y = vheight + y;
	}
	float x = (this->x / vwidth) * 2.0f - 1.0f;
	y = -1.0f * ((y / vheight) * 2.0f - 1.0f);
	float width = (this->width / vwidth) * 2.0f;
	float height = -1.0f * ((this->height / vheight) * 2.0f);



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
		x,			 y + height, 0.0f,
		 x + width,  y + height, 0.0f,
		 x + width, y, 0.0f,
		x,			 y + height, 0.0f,
		 x + width, y, 0.0f,
		 x,			 y, 0.0f
	};

	auto defaultShader = getDefault2DShader();
	vao = std::shared_ptr<TexturedColouredVAO>(new TexturedColouredVAO(defaultShader->programID, 6, vertices, sizeof(vertices), colours, sizeof(colours),
		textures, sizeof(textures)));

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
	auto shader = getDefault2DShader();
	shader->bindShader();
	renderTexture->bind();
	shader->glUniform1("texture1", 0);
	vao->draw();
}
#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include <string>
#include <memory>
#include "render/texture.h"
#include "gameloop.h"
#include "render/vao.h"
#include "shaders/shader.h"

std::shared_ptr<Shader> getDefault2DShader();

///
/// ComponentBase defines an abstract base class for all user interface components. 
///
class ComponentBase
{
public:
	std::shared_ptr<Texture> renderTexture;
	float width;
	float height;
	float x;
	float y;
	int previousScreenWidth;
	int previousScreenHeight;
	std::shared_ptr<TexturedColouredVAO> vao;

	ComponentBase(std::shared_ptr<Texture> t, float x, float y, float width, float height);
	virtual void draw() = 0;
	virtual void update(MouseManager *manager) = 0;
	void rebuildVAO();
	///
	/// Gets whether or not a point is inside this Component, including whether or not it is inside the border.
	/// \param x the x value of the point to compare
	/// \param y the y value of the point to compare
	/// \return a bool indicating whether the point is in bounds of this component
	///
	bool inBounds(int mouseX, int mouseY);
	void drawBackground();
};


#endif

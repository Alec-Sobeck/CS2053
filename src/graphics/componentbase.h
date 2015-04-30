#pragma once

#include <string>
#include <memory>
#include "render/texture.h"
#include "gameloop.h"
#include "render/vao.h"
#include "shaders/shader.h"

std::shared_ptr<Shader> getDefault2DTextureShader();
std::shared_ptr<Shader> getDefault2DColourShader();

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
	///
	/// Fixes an X value to be in the rendering interval [-1, 1]. The left side of the viewport is -1, and the right side is 1.
	/// Note: a value returned could actually be outside [-1, 1]. This indicates that the value is outside the viewport. 
	/// \param val - the value to bound in the render space [-1, 1].
	/// \return a float which will be bounded be [-1, 1] if it's inside the viewport; or will have a value outside this interval if it's outside the viewport.
	/// 
	float getAdjustedX(float val);
	///
	/// Fixes an Y value to be in the rendering interval [-1, 1]. The bottom side of the viewport is -1, and the top side is 1.
	/// Note: a value returned could actually be outside [-1, 1]. This indicates that the pixel value passed in was outside the viewport. 
	/// \param val - the value to bound in the render space [-1, 1].
	/// \return a float which will be bounded be [-1, 1] if it's inside the viewport; or will have a value outside this interval if it's outside the viewport.
	/// 
	float getAdjustedY(float val);
	///
	/// Fixes a width value to be in the rendering interval [-1, 1]. 
	/// \param val - the value to bound in the render space [-1, 1]
	/// \return a float which will be bounded be [-1, 1] if it's inside the viewport. The value could exceed that if the provided pixel size if wider than the viewport.
	/// 
	float getAdjustedWidth(float val);
	///
	/// Fixes a height value to be in the rendering interval [-1, 1]. If the value passed in is in the interval (0, INF) then the returned value will be
	/// negative because -1 is the bottom of the screen. If the value passed in is in the interval (-INF, 0) then the value returned will be positive.
	/// \param val - the value to bound in the render space [-1, 1]
	/// \return a float which will be bounded be [-1, 1] if it's inside the viewport. The value could exceed that if larger than the viewport.
	/// 
	float getAdjustedHeight(float val);


};


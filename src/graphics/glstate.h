#pragma once

#include "math/gamemath.h"
#include "camera.h"
#include "shaders/shader.h"
#include "utils/utilities.h"


class GLState
{
public:
	///
	/// Shaders
	///
	std::shared_ptr<Shader> default3DShader;
	std::shared_ptr<Shader> default2DTextureShader;
	std::shared_ptr<Shader> default2DColourShader;

	///
	/// 3D state
	///
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	void initializeShaders();
	void update(Camera* camera);
	/// Loads the identity matrix into the model matrix
	void loadIdentity();
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);

	/// ---------------------------------------------------------------------
	/// 2D drawing functions
	/// ---------------------------------------------------------------------
	///
	/// Tests to see if a 2D mouse click is in bounds of a 2D rectangle. This does some funky math because 2D drawing currently has some problems.
	/// All values passed in should be in pixels assuming the lower-left corner of the window is the origin (0, 0)
	/// \param mouseXIn - 
	/// \param mouseYIn - 
	/// \param xIn - 
	/// \param yIn - 
	/// \param widthIn -
	/// \param heightIn - 
	///
	bool inBounds(int mouseXIn, int mouseYIn, int xIn, int yIn, int widthIn, int heightIn);
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



	void draw2DTexturedQuad(std::shared_ptr<Texture> tex, int xIn, int yIn, int widthIn, int heightIn);
	void draw2DTexturedQuad(std::shared_ptr<Texture> tex, int xIn, int yIn, int widthIn, int heightIn, 
		float textureStartX, float textureStartY, float textureEndX, float textureEndY);
	void draw2DColouredQuad(utils::Colour colour, int xIn, int yIn, int widthIn, int heightIn);

	
	/////void draw2DColouredTriangle();

	////void draw2DTexturedTriangle();
	///
	/// Draw coloured circle
	///




};

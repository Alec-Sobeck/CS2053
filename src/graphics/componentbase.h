#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include <string>
#include <memory>
#include "render/texture.h"
#include "gameloop.h"

/**
* GuiComponent defines an abstract base class for all GuiComponents, therefore it may not be instantiated. In order to
* create a custom GuiComponent {@link #update()} and {@link #draw()} methods must be implemented in a subclass.
* @author Alec Sobeck
*/
class ComponentBase
{
public:
	std::shared_ptr<Texture> renderTexture;
	/** The width of the button as a % of the screen, between 0.0F and 1.0F*/
	double width;
	/** The height of the button as a % of the screen, between 0.0F and 1.0F*/
	double height;
	/** The x position as a % of the screen, between 0.0F and 1.0F */
	double x;
	/** The y position as a % of the screen, between 0.0F and 1.0F */
	double y;

	/**
	* Creates a new LWJGLComponent and sets its position and size to the specified values.
	* @param x a double indicating the x position of the component. This might be influenced by the
	* component's LWJGLAlignment as well as whether or not it is at a fixed position
	* @param y a double indicating the y position of the component. This might be influenced by the
	* component's LWJGLAlignment as well as whether or not it is at a fixed position.
	* @param width a double indicating how wide this component will be. This in general will only be
	* affected by whether or not the component is a fixed size.
	* @param height a double indicating how high this component will be. This in general will only be
	* affected by whether or not the component is a fixed size.
	*/
	ComponentBase(std::shared_ptr<Texture> t, double x, double y, double width, double height);

	/**
	* An overridable method to draw the gui component. All GuiComponents must implement this.
	* @param parentOffsetX a double value provided by the parent component which is their position relative to
	* the origin on the x axis. This value should be used when determining the position of the component.
	* @param parentOffsetY a double value provided by the parent component which is their position relative to
	* the origin on the y axis. This value should be used when determining the position of the component.
	*/
	virtual void draw() = 0;
	/**
	* Update is called when the frame's update method is called, which should be on every game tick. If a component needs periodically
	* updated, it should do so using this method.
	*/
	virtual void update(MouseManager *manager) = 0;
	/**
	* Gets whether or not a point is inside this LWJGLComponent, including whether or not it is inside the border.
	* @param x the x value of the point to compare
	* @param y the y value of the point to compare
	* @return a boolean indicating whether the point is in bounds of this component
	*/
	bool inBounds(int mouseX, int mouseY);
	/**
	* Draws some sort of background which is based on the background color, border color, and border style.
	* This may be overridden to do something different in each component.
	* @param parentOffsetX a double which is how far the parent component offsets this component along the x axis
	* @param parentOffsetY a double which is how far the parent component offsets this component along the y axis
	*/
	void drawBackground();
};


#endif

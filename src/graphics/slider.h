#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include <string>
#include "componentbase.h"

/**
* GuiButton implements a more complex button, with a single background texture.
* When the button is clicked it will toggle through the different possible values.
* The value will remain the same if there is only one value.
* @author      Alec Sobeck
*/
class Slider : public ComponentBase
{
public:
	float value;
	/**
	* Constructs a new instance of GuiButton and initializes the button with the specified
	* values.
	* @param text the text that this button will render
	* @param x the x position of the button, as a percent of the screen, from 0.0F to 1.0F
	* @param y the y position of the button, as a percent of the screen, from 0.0F to 1.0F
	*/
	Slider(std::shared_ptr<Texture> tex, double x, double y, double width, double height);
	/**
	 * Draws the button, and fixes the position if the screen has been resized
	 */
	virtual void draw() override;	
	virtual void update(MouseManager *manager) override;
};


#endif

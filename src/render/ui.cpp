
#include <sstream>
#include "render/ui.h"
#include "graphics/windowhelper.h"
#include "math/gamemath.h"
using namespace gl;

void drawUI(GLState &glState, Player &player, MouseManager &mouse, std::shared_ptr<GLFont> font,
	std::shared_ptr<Texture> ammoTexture, std::shared_ptr<Texture> medkitTexture)
{
	int width = getWindowWidth();
	int height = getWindowHeight();
	int width2 = width / 2;
	
	// Draw the backgrounds
	glState.draw2DColouredQuad(utils::Colour(0.25f, 0.25f, 0.25f, 1.0f), width2 - 70, height - 60, 70, 60);
	glState.draw2DColouredQuad(utils::Colour(100.0f / 256.0f, 149.0f / 256.0f, 237.0f / 256.0f, 1.0f), width2 - 68, height - 58, 66, 56);
	glState.draw2DColouredQuad(utils::Colour(0.25f, 0.25f, 0.25f, 1.0f), width2, height - 60, 70, 60);
	glState.draw2DColouredQuad(utils::Colour(100.0f / 256.0f, 149.0f / 256.0f, 237.0f / 256.0f, 1.0f), width2 + 2, height - 58, 66, 56);
	// Draw the icons
	glState.draw2DTexturedQuad(ammoTexture, width2 - 60, height - 50, 50, 50);
	glState.draw2DTexturedQuad(medkitTexture, width2 + 10, height - 50, 50, 50);
	// Draw the text.
	std::stringstream ssa;
	ssa << player.ammoCount;
	std::stringstream ssh;
	ssh << player.healingItemCount;
	font->TextOut(glState, ssa.str(), width2 - 60, height - 20, 0);
	font->TextOut(glState, ssh.str(), width2 + 20, height - 20, 0);
	std::stringstream scoress;
	scoress << "score: " << player.score;
	font->TextOut(glState, scoress.str(), 30, 10, 0);

	///
	/// Draw the health HUD
	/// 
	float radius = 40.0f;	
	int degreeOfCircle = static_cast<int>(360 * player.getHealthPercent());
	glState.drawPartialCircle(utils::Colour(1.0f, 0.0f, 0.0f, 1.0f), radius, glm::vec2(radius, height - radius), degreeOfCircle);
	float smallerRadius = 35.0f;
	glState.drawCompleteCircle(utils::Colour(0.4f, 0.4f, 0.4f, 1.0f), smallerRadius, glm::vec2(radius, height - radius));
}
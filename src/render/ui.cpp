
#include <sstream>
#include "render/ui.h"
#include "graphics/windowhelper.h"
#include "math/gamemath.h"
using namespace gl;

void drawUI(Player &player, MouseManager &mouse, std::shared_ptr<GLFont> font,
	std::shared_ptr<Texture> ammoTexture, std::shared_ptr<Texture> medkitTexture)
{
	int width = getWindowWidth();
	int height = getWindowHeight();
	int width2 = width / 2;

	glDisable(GL_TEXTURE_2D);

	// Draw the backgrounds
	glBegin(GL_QUADS);
		// First poly -- outline
		glColor3f(0.25f, 0.25f, 0.25f); 
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2 - 70, height - 60);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2 - 70, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2, height - 60);
		// First poly -- inner icon
		glColor3f(100.0f / 256.0f, 149.0f / 256.0f, 237.0f / 256.0f); // Light blue
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2 - 68, height - 60);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2 - 68, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2 - 2, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2 - 2, height - 60);
		// Second poly -- outline
		glColor3f(0.25f, 0.25f, 0.25f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2, height - 60);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2 + 70, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2 + 70, height - 60);
		// Second poly -- inner icon
		glColor3f(100.0f / 256.0f, 149.0f / 256.0f, 237.0f / 256.0f); // Light blue
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2 + 2, height - 60);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2 + 2, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2 + 68, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2 + 68, height - 60);
	glEnd();

	// Draw the icons
	glEnable(GL_TEXTURE_2D);
	ammoTexture->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2 - 60, height - 50);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2 - 60, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2 - 10, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2 - 10, height - 50);
	glEnd();

	medkitTexture->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(width2 + 10, height - 50);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(width2 + 10, height);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(width2 + 60, height);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(width2 + 60, height - 50);
	glEnd();

	// Draw the text.
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	std::stringstream ssa;
	ssa << player.ammoCount;
	std::stringstream ssh;
	ssh << player.healingItemCount;
	//glScaled(2.0f, 2.0f, 2.0f);
	font->TextOut(ssa.str(), width2 - 60, height - 20, 0);
	font->TextOut(ssh.str(), width2 + 20, height - 20, 0);

	///
	/// Draw the health HUD
	/// 
	glDisable(GL_TEXTURE_2D);
	float degree = 5.0f;
	float radius = 40.0f;
	float rad = toRad(degree);
	int degreeOfCircle = static_cast<int>(360 * player.getHealthPercent() / degree);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(radius, height - radius);
		for (int i = 0; i <= degreeOfCircle; i++)
		{
			float degInRad = i * rad;
			glVertex2f(radius + cos(degInRad) * radius, height - radius + sin(degInRad) * radius);
		}
		glVertex2f(radius, height - radius);
	glEnd();
	// Draw the inner circle.
	float smallerRadius = 35.0f;
	glColor3f(.4f, .4f, .4f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(radius, height - radius);
	for (int i = 0; i <= 360 / degree; i++)
	{
		float degInRad = i * rad;
		glVertex2f(radius + cos(degInRad) * smallerRadius, height - radius + sin(degInRad) * smallerRadius);
	}
	glVertex2f(radius, height - radius);
	glEnd();

	// Score
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	std::stringstream scoress;
	scoress << "score: " << player.score;
	font->TextOut(scoress.str(), 30, 10, 0);
}
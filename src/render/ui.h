#pragma once

#include <memory>
#include "entity/player.h"
#include "gui/glfont.h"
#include "render/texture.h"
#include "gameloop.h"


void drawUI(GLState &glState, Player &player, MouseManager &mouse, std::shared_ptr<GLFont> font,
	std::shared_ptr<Texture> ammoTexture, std::shared_ptr<Texture> medkitTexture);

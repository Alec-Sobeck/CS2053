#ifndef ENGINE_UI_H
#define ENGINE_UI_H

#include <memory>
#include "entity/player.h"
#include "render/glfont.h"
#include "render/texture.h"
#include "gameloop.h"


void drawUI(Player &player, MouseManager &mouse, std::shared_ptr<GLFont> font, 
	std::shared_ptr<Texture> ammoTexture, std::shared_ptr<Texture> medkitTexture);

#endif
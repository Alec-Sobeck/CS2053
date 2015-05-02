
#include <sstream>
#include "menu.h"
#include "graphics/windowhelper.h"

///
/// Define Menu class methods
///
Menu::Menu() 
	: shouldPopMenu(false)
{
}

bool Menu::shouldPopThisMenu()
{
	return shouldPopMenu;
}

///
/// Define the MainMenu class
/// 
MainMenu::MainMenu(std::shared_ptr<Texture> desertText, std::shared_ptr<Texture> forestTex, std::shared_ptr<Texture> helpTex, std::shared_ptr<Texture> optionsTex, 
	std::function<void()> desertEvent, std::function<void()> forestEvent, std::function<void()> helpEvent, std::function<void()> optionsEvent,
	std::shared_ptr<Texture> logo) 
	: Menu(), startDesertLevel(Button(desertText, 10, -170, 256, 32)), startForestLevel(Button(forestTex, 10, -130, 256, 32)), 
	helpButton(Button(helpTex, 10, -90, 256, 32)), optionsButton(Button(optionsTex, 10, -50, 256, 32)),
	desertEvent(desertEvent), forestEvent(forestEvent), helpEvent(helpEvent), optionsEvent(optionsEvent), 
	mainMenuLogo(Logo(logo, getWindowWidth() / 2 - 256, 0, 512, 512))
{
}

void MainMenu::draw(GLState &glState, float deltaTime)
{
	startDesertLevel.draw(glState);
	startForestLevel.draw(glState);
	helpButton.draw(glState);
	optionsButton.draw(glState);
	// Force the logo to be centered, then draw it. This won't change the state of the VAO unless the window size changes, which will invalidate 
	// it anyway.
	mainMenuLogo.x = getWindowWidth() / 2 - 256;
	mainMenuLogo.y = 0;
	mainMenuLogo.width = 512;
	mainMenuLogo.height = 512;
	mainMenuLogo.draw(glState);
}

void MainMenu::update(GLState &glState, MouseManager *manager, float deltaTime)
{
	if (glState.inBounds(manager->x, manager->y, startDesertLevel.x, startDesertLevel.y, startDesertLevel.width, startDesertLevel.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		desertEvent();
	}
	if (glState.inBounds(manager->x, manager->y, startForestLevel.x, startForestLevel.y, startForestLevel.width, startForestLevel.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		forestEvent();
	}
	if (glState.inBounds(manager->x, manager->y, helpButton.x, helpButton.y, helpButton.width, helpButton.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		helpEvent();
	}
	if (glState.inBounds(manager->x, manager->y, optionsButton.x, optionsButton.y, optionsButton.width, optionsButton.height) &&
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		optionsEvent();
	}
}

///
/// Define the OptionsMenu class
/// 
OptionsMenu::OptionsMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> volumeTexture, float volume, std::function<void(float)> onVolumeChange) 
	: Menu(), backButton(Button(backTex, 10, -50, 256, 32)), volumeSlider(Slider(volumeTexture, 10, 30, 256, 32)), onVolumeChange(onVolumeChange)
{
	volumeSlider.value = volume;
}

void OptionsMenu::draw(GLState &glState, float deltaTime)
{
	backButton.draw(glState);
	volumeSlider.x = (getWindowWidth() / 2) - (volumeSlider.width / 2);
	volumeSlider.draw(glState);
}

void OptionsMenu::update(GLState &glState, MouseManager *manager, float deltaTime)
{
	volumeSlider.update(glState, manager);
	onVolumeChange(volumeSlider.value);
	if (glState.inBounds(manager->x, manager->y, backButton.x, backButton.y, backButton.width, backButton.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		shouldPopMenu = true;
	}
}

///
/// define the HelpMenu class
///
HelpMenu::HelpMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> guide) 
	: Menu(), backButton(Button(backTex, 10, -50, 256, 32)), helpLogo(Logo(guide, 30, 50, 512, 512))
{
}

void HelpMenu::draw(GLState &glState, float deltaTime)
{
	backButton.draw(glState);
	helpLogo.draw(glState);
}

void HelpMenu::update(GLState &glState, MouseManager *manager, float deltaTime)
{
	if (glState.inBounds(manager->x, manager->y, backButton.x, backButton.y, backButton.width, backButton.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		shouldPopMenu = true;
	}
}

///
/// Define the GameOverMenu class
/// 
GameOverMenu::GameOverMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> gameOverTexture, int score, std::shared_ptr<GLFont> renderer) 
	: Menu(), backButton(Button(backTex, 10, -50, 256, 32)), score(score), fontRenderer(renderer),
	gameOverLogo(Logo(gameOverTexture, getWindowWidth() / 2 - 256, 50, 512, 512))
{
}

void GameOverMenu::draw(GLState &glState, float deltaTime)
{
	using namespace gl;
	backButton.draw(glState);

	// Force the logo to be centered, then draw it. This won't change the state of the VAO unless the window size changes, which will invalidate 
	// it anyway.
	gameOverLogo.x = getWindowWidth() / 2 - 256;
	gameOverLogo.y = 50;
	gameOverLogo.width = 512;
	gameOverLogo.height = 512;
	gameOverLogo.draw(glState);
}

void GameOverMenu::update(GLState &glState, MouseManager *manager, float deltaTime)
{
	if (glState.inBounds(manager->x, manager->y, backButton.x, backButton.y, backButton.width, backButton.height) && 
		manager->leftMouseButtonState == MouseManager::MOUSE_JUST_PRESSED)
	{
		shouldPopMenu = true;
	}
}
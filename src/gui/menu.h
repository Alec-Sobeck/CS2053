#pragma once

#include <stack>
#include <functional>
#include "gui/button.h"
#include "gameloop.h"
#include "gui/slider.h"
#include "glfont.h"
#include "gui/logo.h"

class Menu
{
protected:
	bool shouldPopMenu;
public: 
	Menu();
	virtual void draw(GLState &glState, float deltaTime) = 0;
	virtual void update(GLState &glState, const MouseManager& manager, float deltaTime) = 0;
	bool shouldPopThisMenu();
};

class MainMenu : public Menu
{
private:
	Button startDesertLevel;
	Button startForestLevel;
	Button helpButton;
	Button optionsButton;
	Logo mainMenuLogo;
	std::function<void()> desertEvent;
	std::function<void()> forestEvent;
	std::function<void()> helpEvent;
	std::function<void()> optionsEvent;

public:
	MainMenu(std::shared_ptr<Texture> desertText, std::shared_ptr<Texture> forestTex, std::shared_ptr<Texture> helpTex, std::shared_ptr<Texture> optionsTex,
		std::function<void()> desertEvent, std::function<void()> forestEvent, std::function<void()> helpEvent, std::function<void()> optionsEvent, 
		std::shared_ptr<Texture> logo);
	void draw(GLState &glState, float deltaTime) override;
	void update(GLState &glState, const MouseManager &manager, float deltaTime) override;
};

class OptionsMenu : public Menu
{
private:
	Slider volumeSlider;
	Button backButton;
	std::function<void(float)> onVolumeChange;
public:
	OptionsMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> volumeTexture, float volume, std::function<void(float)> onVolumeChange);
	void draw(GLState &glState, float deltaTime) override;
	void update(GLState &glState, const MouseManager &manager, float deltaTime) override;
};

class HelpMenu : public Menu
{
private:
	Button backButton;
	Logo helpLogo;

public:
	HelpMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> guide);
	void draw(GLState &glState, float deltaTime) override;
	void update(GLState &glState, const MouseManager &manager, float deltaTime) override;
};

class GameOverMenu : public Menu
{
private:
	Button backButton;
	Logo gameOverLogo;
	int score;
	std::shared_ptr<GLFont> fontRenderer;

public:
	GameOverMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> gameOverTexture, int score, std::shared_ptr<GLFont> renderer);
	void draw(GLState &glState, float deltaTime) override;
	void update(GLState &glState, const MouseManager &manager, float deltaTime) override;
};


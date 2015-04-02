#ifndef ENGINE_MENU_H
#define ENGINE_MENU_H
#include <stack>
#include <functional>
#include "graphics/button.h"
#include "gameloop.h"


class Menu
{
protected:
	bool shouldPopMenu;
public: 
	Menu();
	virtual void draw(float deltaTime) = 0;
	virtual void update(MouseManager* manager, float deltaTime) = 0;
	bool shouldPopThisMenu();
};

class MainMenu : public Menu
{
private:
	Button startDesertLevel;
	Button startForestLevel;
	Button helpButton;
	Button optionsButton;
	std::function<void()> desertEvent;
	std::function<void()> forestEvent;
	std::function<void()> helpEvent;
	std::function<void()> optionsEvent;

public:
	MainMenu(std::shared_ptr<Texture> desertText, std::shared_ptr<Texture> forestTex, std::shared_ptr<Texture> helpTex, std::shared_ptr<Texture> optionsTex,
		std::function<void()> desertEvent, std::function<void()> forestEvent, std::function<void()> helpEvent, std::function<void()> optionsEvent);
	void draw(float deltaTime);
	void update(MouseManager* manager, float deltaTime);
};

class OptionsMenu : public Menu
{
private:
//	Button <DO SOMETHING>
	Button backButton;
public:
	OptionsMenu(std::shared_ptr<Texture> backTex);
	void draw(float deltaTime);
	void update(MouseManager* manager, float deltaTime);
};

class HelpMenu : public Menu
{
private:
	Button backButton;
	std::shared_ptr<Texture> guide;
public:
	HelpMenu(std::shared_ptr<Texture> backTex, std::shared_ptr<Texture> guide);
	void draw(float deltaTime);
	void update(MouseManager* manager, float deltaTime);
};

class GameOverMenu : public Menu
{
private:
	Button backButton;
public:
	GameOverMenu(std::shared_ptr<Texture> backTex);
	void draw(float deltaTime);
	void update(MouseManager* manager, float deltaTime);
};


#endif
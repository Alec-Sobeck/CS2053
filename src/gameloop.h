///
/// Only include this header file at the entry point of the application
///
#ifndef ENGINE_GAMELOOP_H
#define ENGINE_GAMELOOP_H

#include <glm/vec3.hpp>

void entryCall(int argc, char **argv);

class MouseManager
{
public:
	static const int MOUSE_RELEASED = 0;
	static const int MOUSE_PRESSED = 1;
	static const int MOUSE_JUST_PRESSED = 2;
	int leftMouseButtonState;
	int middleMouseButtonState;
	int rightMouseButtonState;
	int x;
	int y;
	bool grabbed;
	glm::vec3 relativeGrabDirection;
	MouseManager();
	void setGrabbed(bool);
	void update();
	glm::vec3 getRelativeGrabDirection();
};

class KeyManager
{
public:
	static const int VALID_NUMBER_OF_CHARS = 1000000;
	static const int VALID_NUMBER_OF_SPECIALS = 1000;
	static const unsigned char RELEASED = 1;
	static const unsigned char PRESSED = 2;
	static const int KEY_F1 = 3;
	static const int KEY_F2 = 4;
	static const int KEY_F3 = 5;
	static const int KEY_F4 = 6;
	static const int KEY_F5 = 7;
	static const int KEY_F6 = 8;
	static const int KEY_F7 = 9;
	static const int KEY_F8 = 10;
	static const int KEY_F9 = 11;
	static const int KEY_F10 = 12;
	static const int KEY_F11 = 13;
	static const int KEY_F12 = 14;
	static const int KEY_LEFT = 15;
	static const int KEY_RIGHT = 16;
	static const int KEY_UP = 17;
	static const int KEY_DOWN = 18;
	static const int KEY_PAGE_UP = 19;
	static const int KEY_PAGE_DOWN = 20;
	static const int KEY_PAGE_HOME = 21;
	static const int KEY_PAGE_END = 22;
	static const int KEY_PAGE_INSERT = 23;

	unsigned char keystates[VALID_NUMBER_OF_CHARS];
	unsigned char specialKeystates[VALID_NUMBER_OF_SPECIALS];
	bool isShiftDown;
	bool isControlDown;
	bool isAltDown;
	unsigned char getKeyState(unsigned char key);
	unsigned char isKeyDown(unsigned char key);
	unsigned char getSpecialState(int key);
	KeyManager();
	void update();
	void updateModifierState();
};

#endif

#ifndef ENG_KEY_MANAGER_H
#define ENG_KEY_MANAGER_H

class KeyManager
{
private:
    static const int VALID_NUMBER_OF_CHARS = 1000000;
    unsigned char keystates[VALID_NUMBER_OF_CHARS];
public:
    unsigned const char JUST_PRESSED = 0;
    unsigned const char RELEASED = 1;
    unsigned const char STILL_PRESSED = 2;

    KeyManager();
    void keyPressed (unsigned char key, int x, int y);
    void keyUp (unsigned char key, int x, int y);
    void keySpecial(int key, int x, int y);
    void keySpecialUp(int key, int x, int y);
    bool isKeyDown(unsigned char key);
    bool isSpecialDown(int key);
    bool isShiftDown();
    bool isControlDown();
    bool isAltDown();
    bool update();

};







#endif

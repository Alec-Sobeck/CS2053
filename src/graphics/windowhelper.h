#ifndef WINDOW_HELPER_H
#define WINDOW_HELPER_H

#include <string>

bool initFreeglut(int argc, char **argv);
bool createWindow(int x, int y, int width, int height, std::string windowTitle);
void changeSize(int w, int h);
int getWindowWidth();
int getWindowHeight();


#endif


#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include <GL/freeglut.h>
#include "graphics/rendersettingshelper.h"

bool initFreeglut(int argc, char **argv)
{
    glutInit(&argc, argv);
    return true;
}

bool createWindow(int x, int y, int width, int height, std::string windowTitle)
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());
    return true;
}

void changeSize(int w, int h)
{
	initializeViewport();
}

int getWindowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

int getWindowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}







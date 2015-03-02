
#include "windowhelper.h"
#include <glbinding/gl/gl.h>
#include <GL/freeglut.h>

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
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int getWindowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}

int getWindowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}







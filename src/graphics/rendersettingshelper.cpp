#include <glbinding/gl/gl.h>
#include "graphics/rendersettingshelper.h"

void initializeViewport()
{
    using namespace gl;
    // http://architects.dzone.com/articles/opengl-2d-independent
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Both these values must be your real window size, so of course these values can't be static
    int screenWidth = static_cast<int>(getWindowWidth());
    int screenHeight = static_cast<int>(getWindowHeight());
    float targetAspectRatio = static_cast<float>(virtual_width) / virtual_height;

    // figure out the largest area that fits in this resolution at the desired aspect ratio
    int width = screenWidth;
    int height = static_cast<int>(width / targetAspectRatio + 0.5f);
    if (height > screenHeight)
    {
        //It doesn't fit our height, we must switch to pillarbox then
        height = screenHeight;
        width = static_cast<int>(height * targetAspectRatio + 0.5f);
    }

    // set up the new viewport centered in the backbuffer
    int vpX = (screenWidth  / 2) - (width / 2);
    int vpY = (screenHeight / 2) - (height/ 2);

    glViewport(vpX, screenHeight - (vpY + height), width, height); //Setup the second element for 2D projection

    glEnable(GL_DEPTH_TEST);
    glOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1); //initialize the 2D drawing area
 
    glClearColor(0.0F, 0.0F, 0.0F, 0.0F); //Clear the colour
    glEnable(GL_TEXTURE_2D); //Allow flat textures to be drawn
}

void start2DRenderCycle()
{
    using namespace gl;
    glOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1); //initialize the 2D drawing area
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
}

void end2DRenderCycle()
{
}

void end3DRenderCycle()
{
}

void startRenderCycle()
{
    using namespace gl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0, 0, 0);
}

float getAspectRatio()
{
    return static_cast<float>(getWindowWidth()) / getWindowHeight();
}

int getViewportWidth()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[2];
}

int getViewportHeight()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[3];
}

int getViewportX()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[0];
}

int getViewportY()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[1];
}

void start3DRenderCycle()
{
    using namespace gl;
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}

#include <GL/freeglut.h>
void endRenderCycle()
{
	glutSwapBuffers();
}

#include "graphics/glincludes.h"
#include "graphics/rendersettingshelper.h"
#include "graphics/gluhelper.h"

const int virtual_width = 1280;
const int virtual_height = 720;

/**
 * Initializes the default 2D openGL settings, making the resolution of the game math the approximate width and height required.
 */
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //Reset to the origin
    glOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1); //initialize the 2D drawing area
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Reset position to the origin
    glTranslatef(0.0F, 0.0F, 1); //Move out on the screen so stuff is actually visible

    glClearColor(0.0F, 0.0F, 0.0F, 0.0F); //Clear the colour
    glDisable(GL_LIGHTING); //Ensure lighting isnt enabled
    glEnable(GL_TEXTURE_2D); //Allow flat textures to be drawn
    glDisable(GL_FOG); //Ensure there isnt fog enabled
//		System.out.println(x + " " + y + " " + width + " " + height);
    // set up lighting
//	    GL11.glEnable(GL11.GL_LIGHTING);
//	    GL11.glEnable(GL11.GL_LIGHT0);
//	    GL11.glMaterial(GL11.GL_FRONT, GL11.GL_SPECULAR, floatBuffer(1.0f, 1.0f, 1.0f, 1.0f));
//	    GL11.glMaterialf(GL11.GL_FRONT, GL11.GL_SHININESS, 25.0f);
//	    GL11.glLight(GL11.GL_LIGHT0, GL11.GL_POSITION, floatBuffer(-5.0f, 5.0f, 15.0f, 0.0f));
//	    GL11.glLight(GL11.GL_LIGHT0, GL11.GL_SPECULAR, floatBuffer(1.0f, 1.0f, 1.0f, 1.0f));
//	    GL11.glLight(GL11.GL_LIGHT0, GL11.GL_DIFFUSE, floatBuffer(1.0f, 1.0f, 1.0f, 1.0f));
//	    GL11.glLightModel(GL11.GL_LIGHT_MODEL_AMBIENT, floatBuffer(0.1f, 0.1f, 0.1f, 1.0f));
}

/**
 * Assuming proper 2D OpenGL rendering settings have been applied, this method will prepare for 2D rendering.
 * The screen will be cleared and GL11.glPushMatrix() is called.
 */
void start2DRenderCycle()
{
    using namespace gl;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, getWindowWidth(), getWindowHeight(), 0, -1, 1); //initialize the 2D drawing area
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
}

/**
 * Assuming a proper 2D OpenGL render cycle has nearly completed, this method will call
 * GL11.glPopMatrix() and then update the Display to finish that render cycle.
 */
void end2DRenderCycle()
{
    using namespace gl;
    glPopMatrix();
}

void end3DRenderCycle()
{
    using namespace gl;
    glPopMatrix();
}

void startRenderCycle()
{
    using namespace gl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0.0f, 0, 0, 0);
    glColor4f(1, 1, 1, 1);
}

void endRenderCycle()
{
    using namespace gl;
    // TODO -- update
    // Display.update();
    swapBuffers();
}

/**
 * Gets the aspect ratio for the current canvas. The aspect ratio is the ratio of x (width) to y (height).
 * @return a float which is the aspect ratio of the current render canvas
 */
float getAspectRatio()
{
    return static_cast<float>(getViewportWidth()) / getViewportHeight();
}

/**
 * Gets the width of the current glViewport
 * @return an int which is the width of the current glViewport
 */
int getViewportWidth()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    return viewport[2];
}

/**
 * Gets the height of the current glViewport
 * @return an int which is the height of the current glViewport
 */
int getViewportHeight()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    return viewport[3];
}

/**
 * Gets the x position of the current glViewport
 * @return an int which is the x position of the current glViewport
 */
int getViewportX()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    return viewport[0];
}

/**
 * Gets the y position of the current glViewport
 * @return an int which is the y position of the current glViewport
 */
int getViewportY()
{
    using namespace gl;
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    return viewport[1];
}

void start3DRenderCycle()
{
    using namespace gl;
    // set up the camera
    //TODO improve the camera and field of view settings

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    gl::glLoadIdentity();
    setGluPerspective(45.0f, getAspectRatio(), 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    gl::glLoadIdentity();
    gl::glPushMatrix();
}

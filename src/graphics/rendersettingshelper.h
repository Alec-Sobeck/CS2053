#ifndef RENDER_SETTINGS_HELPER_H
#define RENDER_SETTINGS_HELPER_H

///
/// RenderSettingsHelper defines functions that set OpenGL settings to some sort of default for a particular operation. For example, 2D or 3D rendering.
///

///
/// Initializes the default 2D openGL settings, making the resolution of the game math the approximate width and height required.
///
void initializeViewport();
///
/// Assuming proper 2D OpenGL rendering settings have been applied, this method will prepare for 2D rendering.
/// The screen will be cleared and glPushMatrix() is called.
///
void start2DRenderCycle();
///
/// Assuming a proper 2D OpenGL render cycle has nearly completed, this method will call
/// glPopMatrix() and then update the Display to finish that render cycle.
///
void end2DRenderCycle();
void start3DRenderCycle();
void end3DRenderCycle();
void startRenderCycle();
void endRenderCycle();
///
/// Gets the aspect ratio for the current canvas. The aspect ratio is the ratio of x (width) to y (height).
/// \return a float which is the aspect ratio of the current render canvas
///
float getAspectRatio();
///
/// Gets the width of the current glViewport
/// \return an int which is the width of the current glViewport
///
int getViewportWidth();
///
/// Gets the height of the current glViewport
/// \return an int which is the height of the current glViewport
/// 
int getViewportHeight();
///
/// Gets the x position of the current glViewport
/// \return an int which is the x position of the current glViewport
///
int getViewportX();
///
/// Gets the y position of the current glViewport
/// \return an int which is the y position of the current glViewport
///
int getViewportY();
///
/// Width in pixels of the current window.
///
int getWindowWidth();
///
/// Height in pixels of the current window.
///
int getWindowHeight();





#endif

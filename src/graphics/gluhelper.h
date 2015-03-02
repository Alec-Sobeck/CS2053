#ifndef ENGINE_GLU_HELPER_H
#define ENGINE_GLU_HELPER_H

/**
 * Defines methods to help with GLU usage.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
#include "camera.h"

/**
 * Calls GLU.gluLookAt using the values in the Camera, to accurately determine where to look at the scene.
 */
void setGluLookAt(Camera *camera);

void setGluLookAt(float f1, float f2, float f3,
                    float f4, float f5, float f6,
                    float f7, float f8, float f9);

void swapBuffers();

void setGluPerspective(float f1, float f2, float f3, float f4);


#endif

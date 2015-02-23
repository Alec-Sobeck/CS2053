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
void setGluLookAt(Camera camera);


#endif

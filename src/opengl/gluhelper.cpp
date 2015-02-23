
#include <cmath>
#include <GL/glu.h>
#include "gluhelper.h"

void setGluLookAt(Camera camera)
{
    gluLookAt(
            camera.position.x,
            camera.position.y,
            camera.position.z,

            //Reference point
            camera.position.x + sin(camera.rotation.y),
            camera.position.y - sin(camera.rotation.x),
            camera.position.z - cos(camera.rotation.y),
            //Up Vector
            0,
            cos(camera.rotation.x),
            0
        );
}


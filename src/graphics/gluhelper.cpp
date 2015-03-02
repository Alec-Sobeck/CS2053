
#include <cmath>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "gluhelper.h"

void setGluLookAt(Camera *camera)
{
    gluLookAt(
            camera->position.x,
            camera->position.y,
            camera->position.z,

            //Reference point
            camera->position.x + sin(camera->rotation.y),
            camera->position.y - sin(camera->rotation.x),
            camera->position.z - cos(camera->rotation.y),
            //Up Vector
            0,
            cos(camera->rotation.x),
            0
        );
}

void setGluLookAt(float f1, float f2, float f3,
                    float f4, float f5, float f6,
                    float f7, float f8, float f9)
{
    gluLookAt(
    f1, f2, f3,
    f4, f5, f6,
    f7, f8, f9

    );

}

void setGluPerspective(float f1, float f2, float f3, float f4)
{
    gluPerspective(f1, f3, f3, f4);
}

void swapBuffers()
{
    glutSwapBuffers();
}


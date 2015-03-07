
#include <cmath>
#include "gluhelper.h"

///
/// Implements gluPerspective() using glbinding. Using the functions defined in GL/glu.h will not work.
///
/// \param fov -- takes an angle measure not a radian.
///
void setPerspective(gl::GLfloat fov, gl::GLfloat aspect, gl::GLfloat zNear, gl::GLfloat zFar)
{
    gl::GLfloat fH = tan( static_cast<float>(fov / 360.0f * 3.14159f)) * zNear;
    gl::GLfloat fW = fH * aspect;
    gl::glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

///
/// Implements gluLookAt() using glbinding. Using the functions defined in GL/glu.h will not work.
///
void setLookAt(Camera *camera)
{
    setLookAt(
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

///
/// Implements gluLookAt() using glbinding. Using the functions defined in GL/glu.h will not work.
///
void setLookAt(gl::GLfloat eyex, gl::GLfloat eyey, gl::GLfloat eyez,
               gl::GLfloat centerx, gl::GLfloat centery, gl::GLfloat centerz,
               gl::GLfloat upx, gl::GLfloat upy, gl::GLfloat upz)
{
    gl::GLfloat m[16];
    gl::GLfloat x[3], y[3], z[3];
    gl::GLfloat mag;
    /* Make rotation matrix */
    /* Z vector */
    z[0] = eyex - centerx;

    z[1] = eyey - centery;

    z[2] = eyez - centerz;

    mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);

    if (mag) {                   /* mpichler, 19950515 */

       z[0] /= mag;

       z[1] /= mag;

       z[2] /= mag;

    }



    /* Y vector */

    y[0] = upx;

    y[1] = upy;

    y[2] = upz;



    /* X vector = Y cross Z */

    x[0] = y[1] * z[2] - y[2] * z[1];

    x[1] = -y[0] * z[2] + y[2] * z[0];

    x[2] = y[0] * z[1] - y[1] * z[0];



    /* Recompute Y = Z cross X */

    y[0] = z[1] * x[2] - z[2] * x[1];

    y[1] = -z[0] * x[2] + z[2] * x[0];

    y[2] = z[0] * x[1] - z[1] * x[0];



    /* mpichler, 19950515 */

    /* cross product gives area of parallelogram, which is < 1.0 for

     * non-perpendicular unit-length vectors; so normalize x, y here

     */



    mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);

    if (mag) {

       x[0] /= mag;

       x[1] /= mag;

       x[2] /= mag;

    }

    mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);

    if (mag) {

       y[0] /= mag;

       y[1] /= mag;

       y[2] /= mag;

    }



 #define M(row,col)  m[col*4+row]

    M(0, 0) = x[0];

    M(0, 1) = x[1];

    M(0, 2) = x[2];

    M(0, 3) = 0.0;

    M(1, 0) = y[0];

    M(1, 1) = y[1];

    M(1, 2) = y[2];

    M(1, 3) = 0.0;

    M(2, 0) = z[0];

    M(2, 1) = z[1];

    M(2, 2) = z[2];

    M(2, 3) = 0.0;

    M(3, 0) = 0.0;

    M(3, 1) = 0.0;

    M(3, 2) = 0.0;

    M(3, 3) = 1.0;

 #undef M

    gl::glMultMatrixf(m);



    /* Translate Eye to Origin */

    gl::glTranslatef(-eyex, -eyey, -eyez);



 }


#include <GL/freeglut.h>
void swapBuffers()
{
    glutSwapBuffers();
}


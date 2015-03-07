#ifndef ENGINE_GLU_HELPER_H
#define ENGINE_GLU_HELPER_H

///
/// gluhelper.h defines functions which do the same thing as functions from the glu library, but instead make
/// use of glbinding. Do not use the GL/glu.h include as the functions will have no effect.
///
#include <glbinding/gl/gl.h>
#include "camera.h"


///
/// Implements gluPerspective() using glbinding. Using the functions defined in GL/glu.h will not work.
///
/// \param fov -- takes an angle measure not a radian.
///
void setPerspective(gl::GLfloat fov, gl::GLfloat aspect, gl::GLfloat zNear, gl::GLfloat zFar);
///
/// Implements gluLookAt() using glbinding. Using the functions defined in GL/glu.h will not work.
///
void setLookAt(Camera *camera);
///
/// Implements gluLookAt() using glbinding. Using the functions defined in GL/glu.h will not work.
///
void setLookAt(gl::GLfloat eyex, gl::GLfloat eyey, gl::GLfloat eyez,
               gl::GLfloat centerx, gl::GLfloat centery, gl::GLfloat centerz,
               gl::GLfloat upx, gl::GLfloat upy, gl::GLfloat upz);

void swapBuffers();

#endif

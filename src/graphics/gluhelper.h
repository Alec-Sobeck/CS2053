#ifndef ENGINE_GLU_HELPER_H
#define ENGINE_GLU_HELPER_H

///
/// gluhelper.h defines functions which do the same thing as functions from the glu library, but instead make
/// use of glbinding. Do not use the GL/glu.h include as the functions will have no effect.
///

void swapBuffers();

#endif

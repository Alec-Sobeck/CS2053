#include "textureloader.h"

#include <soil/SOIL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>


std::shared_ptr<Texture> getTexture(std::string resourceName)
{
    return std::shared_ptr<Texture>(new Texture(
        resourceName,
        static_cast<GLuint>(SOIL_load_OGL_texture(
            resourceName.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ))
    ));

}





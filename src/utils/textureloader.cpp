#include "textureloader.h"

#include <soil/SOIL.h>
#include <glbinding/gl/gl.h>

std::shared_ptr<Texture> getTexture(std::string resourceName)
{
    using namespace gl;
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





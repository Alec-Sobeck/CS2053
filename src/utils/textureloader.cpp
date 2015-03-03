#include "textureloader.h"

#include <soil/SOIL.h>
#include <glbinding/gl/gl.h>

std::shared_ptr<Texture> getTexture(std::string resourceName)
{
    std::shared_ptr<Texture> tex(new Texture(
        resourceName,
        static_cast<gl::GLuint>(SOIL_load_OGL_texture(
            resourceName.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ))
    ));

    gl::glBindTexture(gl::GL_TEXTURE_2D, tex->textureID);
	gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, static_cast<gl::GLint>(gl::GL_LINEAR));
	gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, static_cast<gl::GLint>(gl::GL_LINEAR));
    return tex;
}






#include "texture.h"

using namespace gl;

Texture::Texture(std::string associatedFileName, gl::GLuint textureID) 
	: textureID(textureID), associatedFileName(associatedFileName)
{
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


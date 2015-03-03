
#include "texture.h"

using namespace gl;

/**
 * Constructs a new Texture object, storing the specified textureID for binding
 * @param textureID the Integer representing the texture that can be bound
 */
Texture::Texture(std::string associatedFileName, gl::GLuint textureID) : textureID(textureID), associatedFileName(associatedFileName)
{
}

/**
 * Binds the texture using GL11. The texture will remain bound until the next bind() call of a different
 * texture object, or manual call to GL11.glBindTexture(...)
 */
void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}


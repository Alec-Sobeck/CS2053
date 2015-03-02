
#include "vbo.h"
#include "render/render.h"
#include <iostream>

/**
 * Convience method to create a VBOID. Equivalent to a call to GL15.glGenBuffers().
 * @return a unique int ID that can be used to access a VBO that has been allocated to VRAM
 */
gl::GLuint createVBOID()
{
    gl::GLuint output;
    gl::glGenBuffers(1, &output);
    return output;
}

/**
 * Creates a new VBO and initializes it. This should cause allocation of the data to VRam.
 * @param data a ModelData object that contains the values required to initialize this VBO
 */
VBO::VBO(ModelData &data)
{
    using namespace gl;
   // TODO: texture loading in VBO's is NYI
    this->associatedTexture = nullptr;  //Render::getTexture(data.associatedTextureName);
    this->glRenderMode = data.glRenderMode;
    //This is a brutal check to prevent possible bugs. Things might work for these render modes,
    //but because they haven't been tested it's not worth the risk.
    if (glRenderMode == GL_POINTS || glRenderMode == GL_LINES || glRenderMode == GL_LINE_STRIP ||
        glRenderMode == GL_LINE_LOOP || glRenderMode == GL_POLYGON)
    {
        throw std::invalid_argument("Illegal glRenderMode parameter provided. Only GL_TRIANGLE, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, QL_QUADS, and GL_QUAD_STRIP are supported. ");
    }

    //Vertex stuff
    this->vertexSize = data.vertexSize;
    this->vertexOffset = data.vertexOffset;
    this->vertexType = data.vertexType;
    //Normal stuff
    this->normalSize = data.normalSize;
    this->normalOffset = data.normalOffset;
    this->normalType = data.normalType;
    //Colour stuff
    this->colourSize = data.colourSize;
    this->colourOffset = data.colourOffset;
    this->colourType = data.colourType;
    //Texture stuff
    this->hasTextureData = data.hasTextureData;
    this->textureCoordSize = data.textureCoordSize;
    this->textureCoordOffset = data.textureCoordOffset;
    this->textureCoordType = data.textureCoordType;
    this->elementsPerRowOfCombinedData = data.elementsPerRowOfCombinedData;
    this->stride = data.stride;
    this->combinedData = data.combinedData;
    //Generate applicable buffers
    //Put the values in a FloatBuffer
    //float* vertex_buffer_data = new float[combinedData.size()];
    //vertex_buffer_data.put(combinedData);
    //vertex_buffer_data.rewind();
    float* rawArray = this->combinedData.getRawArray();
    //Create the VBO
    vertexBufferID = createVBOID();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->combinedData.size(), rawArray, GL_STATIC_DRAW);
}

/**
 * Draws the VBO's contents.
 */
void VBO::draw(Camera *camera)
{
    using namespace gl;
    if(!hasTextureData)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        associatedTexture->bind();
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    // render the cube
    glVertexPointer(vertexSize, vertexType, stride, &vertexOffset);
    glNormalPointer(normalType, stride, &normalOffset);
    glColorPointer(colourSize, colourType, stride, &colourOffset);
    glTexCoordPointer(textureCoordSize, textureCoordType, stride, &textureCoordOffset);

    glDrawArrays(glRenderMode, 0, combinedData.size() / elementsPerRowOfCombinedData);
}

VBO::~VBO()
{
    // TODO - fix this method
    // Deletes the VBO from VRAM
    gl::GLuint *buffers = new gl::GLuint[1];
    buffers[0] = static_cast<gl::GLuint>(vertexBufferID);
    gl::glDeleteBuffers(1, buffers);
    delete[] buffers;
}

#ifndef ENGINE_VBO_H
#define ENGINE_VBO_H

#include <memory>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/camera.h"
#include "world/meshdata.h"

gl::GLuint createVBOID();

/**
 * VBO defines an immutable class that takes a ModelData object, ructs a Vertex Buffer Object,
 * and then allows it to be drawn with a call to {@link #draw()}.
 */
class VBO
{
private:
// TODO -- reinstate these const modifiers for all parameters
	 gl::GLenum glRenderMode;
	 int stride;
	 int vertexSize;
	 int vertexOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 gl::GLenum vertexType;
	 int normalSize;
	 int normalOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 gl::GLenum normalType;
	 int colourSize;
	 int colourOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 gl::GLenum colourType;
	 int textureCoordSize;
	 int textureCoordOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 gl::GLenum textureCoordType;
	/** The total number of elements associated to one vertex*/
	 int elementsPerRowOfCombinedData;
	/** The total size of the combined vertex, colour, normal, and texture data in bytes. */
	// FlexArray<float> combinedData;
	 gl::GLuint vertexBufferID;
public:
    bool hasTextureData;
    int totalNumberOfValues;
    std::shared_ptr<Texture> associatedTexture;
	/**
	 * Creates a new VBO and initializes it. This should cause allocation of the data to VRam.
	 * @param data a ModelData object that contains the values required to initialize this VBO
	 */
	VBO(MeshData &data, std::shared_ptr<Texture> texture);

	VBO(std::shared_ptr<MeshData> data, std::shared_ptr<Texture> texture);
	/**
	 * Draws the VBO's contents.
	 */
	void draw(Camera *camera);
	~VBO();
};







#endif

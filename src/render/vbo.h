#ifndef ENGINE_VBO_H
#define ENGINE_VBO_H

#include <GL/glew.h>
#include <GL/gl.h>
#include "render/texture.h"
#include "camera.h"
#include "world/modeldata.h"

/**
 * VBO defines an immutable class that takes a ModelData object, ructs a Vertex Buffer Object,
 * and then allows it to be drawn with a call to {@link #draw()}.
 * @author Alec Sobeck
 * @author Matthew Sobeck
 */
class VBO
{
private:
// TODO -- reinstate these const modifiers for all parameters
	Texture* associatedTexture;
	 int glRenderMode;
	 int stride;
	 int vertexSize;
	 int vertexOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 int vertexType;
	 int normalSize;
	 int normalOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 int normalType;
	 int colourSize;
	 int colourOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 int colourType;
	 int textureCoordSize;
	 int textureCoordOffset;
	/** Corresponds to a GL ant type like GL_FLOAT, or GL_BYTE*/
	 int textureCoordType;
	/** The total number of elements associated to one vertex*/
	 int elementsPerRowOfCombinedData;
	/** The total size of the combined vertex, colour, normal, and texture data in bytes. */
	 FlexArray<float> combinedData;
	 int vertexBufferID;
	bool hasTextureData;

public:
	/**
	 * Creates a new VBO and initializes it. This should cause allocation of the data to VRam.
	 * @param data a ModelData object that contains the values required to initialize this VBO
	 */
	VBO(ModelData &data);
	/**
	 * Draws the VBO's contents.
	 */
	void draw(Camera &camera);
	~VBO();
};







#endif

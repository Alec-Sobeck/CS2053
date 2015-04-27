#ifndef ENGINE_VAO_H
#define ENGINE_VAO_H

#include <memory>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/camera.h"
#include "world/meshdata.h"

///
/// Complements a shader - 
///
class TexturedColouredVAO
{
private:
	gl::GLuint id;
	gl::GLuint buffers[3];
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	gl::GLuint textureLoc;
	int numberOfVertices;

public:
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	TexturedColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize, float *textures, int texturesSize);
	void draw();
};

///
/// Complements a shader - 
///
class ColouredVAO
{
private:
	gl::GLuint id;
	gl::GLuint buffers[2];
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	int numberOfVertices;

public:
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	ColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize);
	void draw();
};






#endif

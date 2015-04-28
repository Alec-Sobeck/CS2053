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
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	gl::GLuint textureLoc;
	int numberOfVertices;

public:
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	TexturedColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize, float *textures, int texturesSize);
	void draw(gl::GLenum renderMode = gl::GL_TRIANGLES);
};

///
/// Complements a shader - 
///
class TexturedNormalColouredVAO
{
private:
	gl::GLuint id;
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	gl::GLuint textureLoc;
	gl::GLuint normalLoc;
	int numberOfVertices;	

public:
	std::shared_ptr<Texture> tex;
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	TexturedNormalColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, 
		float *normals, int normalSize, float *colours, int coloursSize, float *textures, int texturesSize);
	void draw(gl::GLenum renderMode = gl::GL_TRIANGLES);
};

///
/// Complements a shader - 
///
class ColouredVAO
{
private:
	gl::GLuint id;
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	int numberOfVertices;

public:
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	ColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize);
	void draw(gl::GLenum renderMode = gl::GL_TRIANGLES);
};






#endif

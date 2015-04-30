#pragma once

#include <memory>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/camera.h"
#include "world/meshdata.h"

///
/// VAOs complement a shader. They require a valid programID for a shader passed into the constructor in order to function properly
///


class TexturedNormalColouredIndexedVAO
{
private:
	gl::GLuint id;
	gl::GLuint vertexLoc;
	gl::GLuint colourLoc;
	gl::GLuint textureLoc;
	gl::GLuint normalLoc;
	gl::GLushort *indexes;
	int numberOfVertices;
	gl::GLuint elementIndex;

public:
	std::shared_ptr<Texture> tex;
	///
	/// Sizes are in bytes, not length of the array. for a float array, size should be the number of elements * 4 
	///
	TexturedNormalColouredIndexedVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize,
		float *normals, int normalSize, float *colours, int coloursSize, float *textures, int texturesSize, gl::GLushort *indexes);
	~TexturedNormalColouredIndexedVAO();
	void draw(gl::GLenum renderMode = gl::GL_TRIANGLES);
};

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





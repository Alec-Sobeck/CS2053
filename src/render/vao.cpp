
#include "vao.h"
#include "render/render.h"
#include "vbo.h"


TexturedColouredVAO::TexturedColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize, float *textures, int texturesSize)
	: numberOfVertices(numberOfVerts)
{
	using namespace gl;
	GLuint vao[1];
	gl::glGenVertexArrays(1, vao);
	this->id = vao[0];

	gl::glBindVertexArray(id);
	GLuint buffers[3];
	gl::glGenBuffers(3, buffers);
	
	colourLoc = gl::glGetAttribLocation(associatedShaderID, "color");
	vertexLoc = gl::glGetAttribLocation(associatedShaderID, "position");
	textureLoc = gl::glGetAttribLocation(associatedShaderID, "textureIn");

	// bind buffer for vertices and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	gl::glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(vertexLoc);
	gl::glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for colors and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	gl::glBufferData(GL_ARRAY_BUFFER, coloursSize, colours, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(colourLoc);
	gl::glVertexAttribPointer(colourLoc, 4, gl::GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for textures and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	gl::glBufferData(GL_ARRAY_BUFFER, texturesSize, textures, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(textureLoc);
	gl::glVertexAttribPointer(textureLoc, 2, gl::GL_FLOAT, GL_FALSE, 0, 0);

}

void TexturedColouredVAO::draw(gl::GLenum renderMode)
{
	gl::glBindVertexArray(id);
	gl::glDrawArrays(renderMode, 0, numberOfVertices);
}


TexturedColouredVAO::~TexturedColouredVAO()
{
	gl::glDeleteVertexArrays(1, &id);
}

ColouredVAO::ColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize, float *colours, int coloursSize)
	: numberOfVertices(numberOfVerts)
{
	using namespace gl;
	GLuint vao[1];
	gl::glGenVertexArrays(1, vao);
	this->id = vao[0];

	gl::glBindVertexArray(id);
	GLuint buffers[2];
	gl::glGenBuffers(2, buffers);

	colourLoc = gl::glGetAttribLocation(associatedShaderID, "color");
	vertexLoc = gl::glGetAttribLocation(associatedShaderID, "position");

	// bind buffer for vertices and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	gl::glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(vertexLoc);
	gl::glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for colors and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	gl::glBufferData(GL_ARRAY_BUFFER, coloursSize, colours, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(colourLoc);
	gl::glVertexAttribPointer(colourLoc, 4, gl::GL_FLOAT, GL_FALSE, 0, 0);
}

void ColouredVAO::draw(gl::GLenum renderMode)
{
	gl::glBindVertexArray(id);
	gl::glDrawArrays(renderMode, 0, numberOfVertices);
}


ColouredVAO::~ColouredVAO()
{
	gl::glDeleteVertexArrays(1, &id);
}

TexturedNormalColouredVAO::TexturedNormalColouredVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize,
		float *normals, int normalSize, float *colours, int coloursSize, float *textures, int texturesSize)
	: numberOfVertices(numberOfVerts)
{
	using namespace gl;
	GLuint vao[1];
	gl::glGenVertexArrays(1, vao);
	this->id = vao[0];

	gl::glBindVertexArray(id);
	GLuint buffers[4];
	gl::glGenBuffers(4, buffers);

	colourLoc = gl::glGetAttribLocation(associatedShaderID, "color");
	vertexLoc = gl::glGetAttribLocation(associatedShaderID, "position");
	textureLoc = gl::glGetAttribLocation(associatedShaderID, "textureIn");
	normalLoc = gl::glGetAttribLocation(associatedShaderID, "normal");

	// bind buffer for vertices and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	gl::glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(vertexLoc);
	gl::glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for colors and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	gl::glBufferData(GL_ARRAY_BUFFER, coloursSize, colours, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(colourLoc);
	gl::glVertexAttribPointer(colourLoc, 4, gl::GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for textures and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	gl::glBufferData(GL_ARRAY_BUFFER, texturesSize, textures, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(textureLoc);
	gl::glVertexAttribPointer(textureLoc, 2, gl::GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for normals and copy data into buffer
	gl::glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	gl::glBufferData(GL_ARRAY_BUFFER, normalSize, normals, GL_STATIC_DRAW);
	gl::glEnableVertexAttribArray(normalLoc);
	gl::glVertexAttribPointer(normalLoc, 3, gl::GL_FLOAT, GL_FALSE, 0, 0);
}

void TexturedNormalColouredVAO::draw(gl::GLenum renderMode)
{
	if (tex)
	{
		tex->bind();
	}
	gl::glBindVertexArray(id);
	gl::glDrawArrays(renderMode, 0, numberOfVertices);
}

TexturedNormalColouredVAO::~TexturedNormalColouredVAO()
{
	gl::glDeleteVertexArrays(1, &id);
}

TexturedNormalColouredIndexedVAO::TexturedNormalColouredIndexedVAO(gl::GLuint associatedShaderID, int numberOfVerts, float *vertices, int verticesSize,
	float *normals, int normalSize, float *colours, int coloursSize, float *textures, int texturesSize, gl::GLushort *indexes)
	: numberOfVertices(numberOfVerts)
{
	using namespace gl;
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	this->id = vao[0];

	glBindVertexArray(id);
	buffers = new GLuint[5];
	glGenBuffers(5, buffers);

	colourLoc = glGetAttribLocation(associatedShaderID, "color");
	vertexLoc = glGetAttribLocation(associatedShaderID, "position");
	textureLoc = glGetAttribLocation(associatedShaderID, "textureIn");
	normalLoc = glGetAttribLocation(associatedShaderID, "normal");

	// bind buffer for vertices and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for colors and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, coloursSize, colours, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colourLoc);
	glVertexAttribPointer(colourLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for textures and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, texturesSize, textures, GL_STATIC_DRAW);
	glEnableVertexAttribArray(textureLoc);
	glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind buffer for normals and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ARRAY_BUFFER, normalSize, normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	 

	// Populate the indexes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfVertices * sizeof(GLushort), indexes, GL_STATIC_DRAW);
}

void TexturedNormalColouredIndexedVAO::draw(gl::GLenum renderMode)
{
	if (tex)
	{
		tex->bind();
	}
	gl::glBindVertexArray(id);
	gl::glDrawElements(renderMode, numberOfVertices, gl::GL_UNSIGNED_SHORT, (void*)0);
}

TexturedNormalColouredIndexedVAO::~TexturedNormalColouredIndexedVAO()
{
	gl::glDeleteVertexArrays(1, &id);
	gl::glDeleteBuffers(5, buffers);
	delete[] buffers;
}

#include <glbinding/gl/gl.h>
#include "glstate.h"
#include "windowhelper.h"
#include "rendersettingshelper.h"

void GLState::initializeShaders()
{
	std::string vertexShaderPath = utils::buildPath("res/shaders/3d_standard_shader.vert");
	std::string fragmentShaderPath = utils::buildPath("res/shaders/3d_standard_shader.frag");
	default3DShader = createShader(&vertexShaderPath, &fragmentShaderPath);

	vertexShaderPath = utils::buildPath("res/shaders/2d_textured_coloured_triangles.vert");
	fragmentShaderPath = utils::buildPath("res/shaders/2d_textured_coloured_triangles.frag");
	default2DTextureShader = createShader(&vertexShaderPath, &fragmentShaderPath);

	vertexShaderPath = utils::buildPath("res/shaders/2d_coloured_triangles.vert");
	fragmentShaderPath = utils::buildPath("res/shaders/2d_coloured_triangles.frag");
	default2DColourShader = createShader(&vertexShaderPath, &fragmentShaderPath);
}

void GLState::update(Camera* camera)
{
	proj = buildProjectionMatrix(53.13f, getAspectRatio(), 0.1f, 1000.0f);
	
	view = createLookAtMatrix(
		camera->position,
		//Reference point
		glm::vec3(
		camera->position.x + sin(camera->rotation.y),
		camera->position.y - sin(camera->rotation.x),
		camera->position.z - cos(camera->rotation.y)
		),
		//Up Vector
		glm::vec3(
		0,
		cos(camera->rotation.x),
		0
		)
	);
	model = MATRIX_IDENTITY_4D;
}

void GLState::scale(float x, float y, float z)
{
	model = construct3DScalingMatrix(x, y, z) * model;
}

void GLState::translate(float x, float y, float z)
{
	model = construct3DTranslationMatrix(x, y, z) * model;
}

void GLState::loadIdentity()
{
	model = MATRIX_IDENTITY_4D;
}

void GLState::rotate(float angle, float x, float y, float z)
{
	if (approximatelyEqual(x, 1.0f))
	{
		model = construct3dRotationMatrixOnX(rad(angle)) * model;
	}
	else if (approximatelyEqual(y, 1.0f))
	{
		model = model * construct3dRotationMatrixOnY(rad(angle));
	}
	else if (approximatelyEqual(z, 1.0f))
	{
		model = construct3dRotationMatrixOnZ(rad(angle)) * model;
	}
	else
	{
		throw std::invalid_argument("Rotation not supported");
	}
}

float GLState::getAdjustedX(float val)
{
	return (val / getViewportWidth()) * 2.0f - 1.0f;
}

float GLState::getAdjustedY(float val)
{
	float y = val;
	if (y < 0)
	{
		y = getViewportHeight() + y;
	}
	return -1.0f * ((y / getViewportHeight()) * 2.0f - 1.0f);
}

float GLState::getAdjustedWidth(float val)
{
	return (val / getViewportWidth()) * 2.0f;

}

float GLState::getAdjustedHeight(float val)
{
	return -1.0f * ((val / getViewportHeight()) * 2.0f);
}

bool GLState::inBounds(int mouseXIn, int mouseYIn, int xIn, int yIn, int widthIn, int heightIn)
{
	// Scale mouseX, mouseY to floats on [-1, 1]
	float mouseX = getAdjustedX(static_cast<float>(mouseXIn - getViewportX()));
	float mouseY = getAdjustedY(static_cast<float>(mouseYIn - getViewportY()));
	// Scale bounding values to [-1, 1]
	float x = getAdjustedX(static_cast<float>(xIn));
	float y = getAdjustedY(static_cast<float>(yIn));
	float width = getAdjustedWidth(static_cast<float>(widthIn));
	float height = getAdjustedHeight(static_cast<float>(heightIn));
	return (between(x, x + width, mouseX) && between(y, y + height, mouseY));
}

void GLState::draw2DTexturedQuad(std::shared_ptr<Texture> tex, int xIn, int yIn, int widthIn, int heightIn)
{
	using namespace gl;
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	GLuint buffers[2];
	gl::glGenBuffers(2, buffers);
	GLuint vertexLoc = gl::glGetAttribLocation(default2DTextureShader->programID, "position");
	GLuint textureLoc = gl::glGetAttribLocation(default2DTextureShader->programID, "textureIn");

	float x = getAdjustedX(xIn);
	float y = getAdjustedY(yIn);
	float width = getAdjustedWidth(widthIn);
	float height = getAdjustedHeight(heightIn);
	float vertices[] = {
		x, y + height, 0.0f,
		x + width, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y, 0.0f
	};
	float textures[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	
	// bind buffer for vertices and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// bind buffer for textures and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
	glEnableVertexAttribArray(textureLoc);
	glVertexAttribPointer(textureLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

	default2DTextureShader->bindShader();
	default2DTextureShader->glUniform1("texture1", 0);
	tex->bind();
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDeleteVertexArrays(1, vao);
}

void GLState::draw2DColouredQuad(utils::Colour colour, int xIn, int yIn, int widthIn, int heightIn)
{
	using namespace gl;
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	GLuint buffers[2];
	gl::glGenBuffers(2, buffers);
	GLuint vertexLoc = gl::glGetAttribLocation(default2DColourShader->programID, "position");
	GLuint colourLoc = gl::glGetAttribLocation(default2DColourShader->programID, "color");

	float x = getAdjustedX(xIn);
	float y = getAdjustedY(yIn);
	float width = getAdjustedWidth(widthIn);
	float height = getAdjustedHeight(heightIn);
	float vertices[] = {
		x, y + height, 0.0f,
		x + width, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y + height, 0.0f,
		x + width, y, 0.0f,
		x, y, 0.0f
	};
	float colours[] = {
		colour.r, colour.g, colour.b, colour.a,
		colour.r, colour.g, colour.b, colour.a,
		colour.r, colour.g, colour.b, colour.a,
		colour.r, colour.g, colour.b, colour.a,
		colour.r, colour.g, colour.b, colour.a,
		colour.r, colour.g, colour.b, colour.a
	};

	// bind buffer for vertices and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// bind buffer for colours and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colourLoc);
	glVertexAttribPointer(colourLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);

	default2DColourShader->bindShader();
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDeleteVertexArrays(1, vao);
}



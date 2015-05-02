#pragma once

#include <string>
#include <map>
#include <memory>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/glstate.h"

namespace GLFontError 
{
	struct InvalidFile{};
	struct InvalidFont{};
}

class GLFontChar
{
public:
	float tx1, tx2, ty1, ty2;
	float width, height;
};

class GLFont 
{
public:
	GLFont();
	~GLFont();
	const int textureWidth = 256;
	const int textureHeight = 256;
	std::map<char, GLFontChar> characters;
	std::shared_ptr<Texture> fontTexture;
	bool ok;

	void Create(std::shared_ptr<Texture> tex);
	void TextOut(GLState &glState, std::string String, float x, float y, float z);
};

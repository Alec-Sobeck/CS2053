#include <cmath>
#include <stdio.h>
#include "glfont.h"
using namespace gl;

GLFont::GLFont() : ok(false)
{
}

void GLFont::Create(std::shared_ptr<Texture> tex)
{
	this->fontTexture = tex;
	float tx = 0.0f;
	float ty = 1.0f;
	for (int i = 1; i <= 9; i++)
	{
		float tx1, tx2, ty1, ty2;
		float width, height;
		GLFontChar c;
		c.tx1 = tx;
		c.tx2 = tx + 16.0f / 256.0f;
		c.ty1 = ty;
		c.ty2 = ty - 16.0f / 256.0f;
		c.width = 16;
		c.height = 16;
		characters.insert({static_cast<char>(48 + i), c });

		tx += 16.0f / 256.0f;
	}
	GLFontChar c;
	c.tx1 = tx + 0.0f / 256.0f;
	c.tx2 = tx + 16.0f / 256.0f;
	c.ty1 = ty;
	c.ty2 = ty - 16.0f / 256.0f;
	c.width = 16;
	c.height = 16;
	characters.insert({ 48 , c });

	tx = 0.0f;
	ty = 1.0f - 16.0f / 256.0f;
	for (char i = 'a'; i <= 'z'; i++)
	{
		if (tx >= 1.0f)
			ty -= 16.0f / 256.0f;
		tx = fmod(tx, 1.0f);
		ty = fmod(ty, 1.0f);

		GLFontChar c;
		c.tx1 = tx;
		c.tx2 = tx + 16.0f / 256.0f;
		c.ty1 = ty;
		c.ty2 = ty - 16.0f / 256.0f;
		c.width = 16;
		c.height = 16;

		characters.insert({ i, c });

		tx += 16.0f / 256.0f;
	}

	tx = 0.0f;
	c.tx1 = tx;
	c.tx2 = tx + 16.0f / 256.0f;
	c.ty1 = ty - 16.0f / 256.0f;
	c.ty2 = ty - 32.0f / 256.0f;
	c.width = 16;
	c.height = 16;
	characters.insert({ ':' , c });

	ok = true;
}

GLFont::~GLFont()
{
	ok = false;
}

void GLFont::TextOut(GLState &glState, std::string String, float x, float y, float z)
{
	if (!ok)
	{
		throw GLFontError::InvalidFont();
	}
	
	//Get length of string
	int Length = String.length();
	
	//Loop through characters
	for (int i = 0; i < Length; i++)
	{
		//Get pointer to glFont character
		GLFontChar* Char = &characters[String[i]];
		glState.draw2DTexturedQuad(fontTexture, x, y, Char->width, Char->height, Char->tx1, Char->ty1, Char->tx2, Char->ty2);

		//Specify vertices and texture coordinates
		/*
		glTexCoord2f(, Char->ty1);
		glVertex2i(x, y);
		glTexCoord2f(Char->tx1, Char->ty2);
		glVertex2i(x, y + Char->height);
		glTexCoord2f(Char->tx2, Char->ty2);
		glVertex2i(x + Char->width, y + Char->height);
		glTexCoord2f(Char->tx2, Char->ty1);
		glVertex2i(x + Char->width, y);
		*/
		//Move to next character
		x += Char->width;
	}

	//Stop rendering quads
	glEnd();
}

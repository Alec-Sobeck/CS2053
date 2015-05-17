
#include <soil/SOIL.h>
#include <glbinding/gl/gl.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <stdexcept>
#include <fstream>
#include "utilities.h"

namespace utils
{

/// ----------------------------------------------------------------------------------------------
/// Time related utilities
///
unsigned long long getCurrentTimeMillis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/// ----------------------------------------------------------------------------------------------
/// Random number related utilities
///
void seedRandomGenerator()
{
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;
		srand(time(NULL));
	}
}

int getRandomInt(int maxValue)
{
	seedRandomGenerator();
	return rand() % maxValue;
}

float getRandomFloat()
{
	seedRandomGenerator();
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/// ----------------------------------------------------------------------------------------------
/// String utilities
/// 
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

double parseDouble(const std::string& s)
{
	std::stringstream i(s);
	double x;
	if (!(i >> x))
	{
		std::stringstream ss;
		ss << "Error: failed to parse double '" << s << "'";
		throw std::invalid_argument(ss.str());
	}
	return x;
}

float parseFloat(const std::string& s)
{
	std::stringstream i(s);
	float x;
	if (!(i >> x))
	{
		std::stringstream ss;
		ss << "Error: failed to parse float '" << s << "'";
		throw std::invalid_argument(ss.str());
	}
	return x;
}


int parseInt(const std::string& s)
{
	std::stringstream i(s);
	int x;
	if (!(i >> x))
	{
		std::stringstream ss;
		ss << "Error: failed to parse int '" << s << "'";
		throw std::invalid_argument(ss.str());
	}
	return x;
}

std::string replaceAll(std::string &searchFor, std::string &replacement, std::string target)
{
	size_t pos = 0;
	while ((pos = target.find(searchFor, pos)) != std::string::npos)
	{
		target.replace(pos, searchFor.length(), replacement);
		pos += replacement.length();
	}
	return target;
}

bool endsWith(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

std::string padNewlines(std::string target)
{
	static std::string searchFor = "\n";
	static std::string replacement = "\n\t\t";
	size_t pos = 0;
	while ((pos = target.find(searchFor, pos)) != std::string::npos)
	{
		target.replace(pos, searchFor.length(), replacement);
		pos += replacement.length();
	}
	return target;
}


/// ----------------------------------------------------------------------------------------------
/// File utilities
///

std::string readTextFile(std::string filepath)
{
	std::ifstream infile(filepath.c_str());
	if (infile.fail())
	{
		std::stringstream ss;
		ss << "Failure to open file at " << filepath;
		throw std::runtime_error(ss.str());
	}
	std::string line;
	std::stringstream content;
	while (std::getline(infile, line))
	{
		content << line << "\n";
	}
	return content.str();
}

void writeTextFile(std::string filepath, std::string contents)
{
	std::ofstream file(filepath.c_str());
	if (file.fail())
	{
		std::stringstream ss;
		ss << "Failure to open file at " << filepath;
		throw std::runtime_error(ss.str());
	}
	file << contents;
	file.close();
}

std::vector<std::string> readTextFileAsLines(std::string filepath)
{
	std::vector<std::string> out;
	std::ifstream infile(filepath.c_str());
	if (infile.fail())
	{
		std::stringstream ss;
		ss << "Failure to open file at " << filepath;
		throw std::runtime_error(ss.str());
	}
	std::string line;
	while (std::getline(infile, line))
	{
		out.push_back(line);
	}
	return out;
}

std::string buildPath(std::string path)
{
#ifdef _WIN32
	static const std::string gameDirectory = "C:/Program Files/Engine/";
#else
#error NYI
	static const std::string gameDirectory = "";
#endif
	std::stringstream ss;
	ss << gameDirectory << path;
	return ss.str();
}

/// ----------------------------------------------------------------------------------------------
/// Texture utilities
///

std::shared_ptr<Texture> getTexture(std::string resourceName)
{
	std::shared_ptr<Texture> tex(new Texture(
		resourceName,
		static_cast<gl::GLuint>(SOIL_load_OGL_texture(
		resourceName.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		))
		));

	gl::glBindTexture(gl::GL_TEXTURE_2D, tex->textureID);
	gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, static_cast<gl::GLint>(gl::GL_LINEAR));
	gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, static_cast<gl::GLint>(gl::GL_LINEAR));
	return tex;
}

/// ----------------------------------------------------------------------------------------------
/// Colours utilities
///

Colour::Colour() : r(0), g(0), b(0), a(0)
{
}

Colour::Colour(double r, double g, double b, double a) : r(r), g(g), b(b), a(a)
{
}

std::string Colour::toString()
{
	std::stringstream ss;
	ss << "(" << r << "," << g << "," << b << "," << a << ")";
	return ss.str();
}


}

#ifndef ENGINE_SPHERE_H
#define ENGINE_SPHERE_H

#include <vector>
#include <glbinding/gl/gl.h>

class Sphere
{
protected:
	std::vector<gl::GLfloat> vertices;
	std::vector<gl::GLfloat> normals;
	std::vector<gl::GLfloat> texcoords;
	std::vector<gl::GLushort> indices;

public:
	Sphere(float radius, unsigned int rings, unsigned int sectors);
	void draw(gl::GLfloat x, gl::GLfloat y, gl::GLfloat z);
};





#endif

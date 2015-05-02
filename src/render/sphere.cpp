
#include <iostream>
#include <cmath>
#include "sphere.h"
#include "math/gamemath.h"

Sphere::Sphere(GLState &glState, float radius, unsigned int rings, unsigned int sectors)
{
	using namespace gl;
	float *vertices = new float[rings * sectors * 3];
	float *normals = new float[rings * sectors * 3];
	float *textures = new float[rings * sectors * 2];
	GLushort *indices = new GLushort[rings * sectors * 4];
	float *colours = new float[rings * sectors * 4];
	
	float const R = 1.0f / static_cast<float>(rings - 1);
	float const S = 1.0f / static_cast<float>(sectors - 1);

	int v = 0;
	int n = 0;
	int t = 0;
	int c = 0;

	for (int r = 0; r < rings; r++) 
	{
		for (int s = 0; s < sectors; s++)
		{
			float const y = sin(-PIOVER2 + PI * r * R);
			float const x = cos(2 * PI * s * S) * sin(PI * r * R);
			float const z = sin(2 * PI * s * S) * sin(PI * r * R);

			textures[t + 0] = s*S;
			textures[t + 1] = r*R;
			t += 2;

			vertices[v + 0] = x * radius;
			vertices[v + 1] = y * radius;
			vertices[v + 2] = z * radius;
			v += 3; 

			normals[n + 0] = x;
			normals[n + 1] = y;
			normals[n + 2] = z;
			n += 3;

			colours[c + 0] = 1.0f;
 			colours[c + 1] = 1.0f;
			colours[c + 2] = 1.0f;
			colours[c + 3] = 1.0f;
			c += 4;
		}
	}

	int i = 0;
	for (int r = 0; r < rings - 1; r++)
	{
		for (int s = 0; s < sectors - 1; s++)
		{
			indices[i + 0] = r * sectors + s;
			indices[i + 1] = r * sectors + (s + 1);
			indices[i + 2] = (r + 1) * sectors + (s + 1);
			indices[i + 3] = (r + 1) * sectors + s;
			i += 4;
		}
	}

	if (!vertices || !normals || !textures || !indices || !colours)
	{
		throw std::invalid_argument("Failure to create sphere: failure to generate float[] of data.");
	}

	vao = std::shared_ptr<TexturedNormalColouredIndexedVAO>(new TexturedNormalColouredIndexedVAO(
		glState.default3DShader->programID, 
		rings * sectors * 4, 
		vertices, rings * sectors * 3 * sizeof(float),
		normals, rings * sectors * 3 * sizeof(float),
		colours, rings * sectors * 4 * sizeof(float),
		textures, rings * sectors * 2 * sizeof(float), 
		indices
	));

	delete[] vertices;
	delete[] normals;
	delete[] textures;
	delete[] colours;
	delete[] indices;
}

void Sphere::draw(GLState &state, std::shared_ptr<Texture> tex, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z)
{
	state.loadIdentity();
	state.translate(x, y, z);
	state.default3DShader->glUniformMatrix4("modelMatrix", gl::GL_FALSE, state.model);
	tex->bind();
	vao->draw();
}

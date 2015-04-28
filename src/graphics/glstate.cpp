
#include <glbinding/gl/gl.h>
#include "glstate.h"
#include "windowhelper.h"
#include "rendersettingshelper.h"

void setLookAtMatrix(glm::mat4 &in, gl::GLfloat eyex, gl::GLfloat eyey, gl::GLfloat eyez,
	gl::GLfloat centerx, gl::GLfloat centery, gl::GLfloat centerz,
	gl::GLfloat upx, gl::GLfloat upy, gl::GLfloat upz)
{
	gl::GLfloat m[16];
	gl::GLfloat x[3], y[3], z[3];
	gl::GLfloat mag;
	// Make rotation matrix 
	// Z vector 
	z[0] = eyex - centerx;
	z[1] = eyey - centery;
	z[2] = eyez - centerz;
	mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
	if (mag)
	{
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
	}
	// Y vector 
	y[0] = upx;
	y[1] = upy;
	y[2] = upz;
	// X vector = Y cross Z 
	x[0] = y[1] * z[2] - y[2] * z[1];
	x[1] = -y[0] * z[2] + y[2] * z[0];
	x[2] = y[0] * z[1] - y[1] * z[0];
	// Recompute Y = Z cross X 
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];

	// cross product gives area of parallelogram, which is < 1.0 for
	// non-perpendicular unit-length vectors; so normalize x, y here
	mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	if (mag)
	{
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
	}

	mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag)
	{
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
	}

#define M(row,col)  m[col*4+row]
	M(0, 0) = x[0];
	M(0, 1) = x[1];
	M(0, 2) = x[2];
	M(0, 3) = 0.0;
	M(1, 0) = y[0];
	M(1, 1) = y[1];
	M(1, 2) = y[2];
	M(1, 3) = 0.0;
	M(2, 0) = z[0];
	M(2, 1) = z[1];
	M(2, 2) = z[2];
	M(2, 3) = 0.0;
	M(3, 0) = 0.0;
	M(3, 1) = 0.0;
	M(3, 2) = 0.0;
	M(3, 3) = 1.0;
#undef M

	in = glm::mat4(
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15]
	);
	in = construct3DTranslationMatrix(-eyex, -eyey, -eyez) * in;


//	gl::glMultMatrixf(m);
	// Translate Eye to Origin 
	//gl::glTranslatef(-eyex, -eyey, -eyez);
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
	/*
	setLookAtMatrix(view,
		camera->position.x,
		camera->position.y,
		camera->position.z,
		//Reference point
		
		camera->position.x + sin(camera->rotation.y),
		camera->position.y - sin(camera->rotation.x),
		camera->position.z - cos(camera->rotation.y),
		
		//Up Vector
		
		0,
		cos(camera->rotation.x),
		0
		
		);
		*/
	model = MATRIX_IDENTITY_4D;
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
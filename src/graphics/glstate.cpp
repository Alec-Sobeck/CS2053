
#include <glbinding/gl/gl.h>
#include "glstate.h"
#include "windowhelper.h"
#include "rendersettingshelper.h"

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


#include "math/gamemath.h"

glm::mat4x4 createLookAtMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	using namespace glm;

	vec3 zaxis = normalize(eye - target);    // The "forward" vector.
	vec3 xaxis = normalize(cross(up, zaxis));// The "right" vector.
	vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.

	// Create a 4x4 orientation matrix from the right, up, and forward vectors
	// This is transposed which is equivalent to performing an inverse 
	// if the matrix is orthonormalized (in this case, it is).
	mat4 orientation = {
		vec4(xaxis.x, yaxis.x, zaxis.x, 0),
		vec4(xaxis.y, yaxis.y, zaxis.y, 0),
		vec4(xaxis.z, yaxis.z, zaxis.z, 0),
		vec4(0, 0, 0, 1)
	};

	// Create a 4x4 translation matrix.
	// The eye position is negated which is equivalent
	// to the inverse of the translation matrix. 
	// T(v)^-1 == T(-v)
	mat4 translation = {
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-eye.x, -eye.y, -eye.z, 1)
	};

	// Combine the orientation and translation to compute 
	// the final view matrix
	return (orientation * translation);	
}



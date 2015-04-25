#ifndef GAMEMATH_H
#define GAMEMATH_H

///
/// Usage note: <cmath> and <glm/glm.hpp> define a lot of operations already. For example, glm defines the following vector operations: 
/// http://glm.g-truc.net/0.9.4/api/a00131.html
/// Functions defined here are supplmentary things which might be useful, but are not defined in <cmath> or <glm/glm.hpp>
/// Including gamemath.h will include these other files by default
/// 

#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include "math/intersection.h"
#include "math/linesegment2.h"

///
/// Constants
/// 
const float PI = 3.14159265359f;
const double PI_D = 3.14159265359;
const float PIOVER2 = 3.14159265359f / 2.0f;
const double PIOVER2_D = 3.14159265359 / 2.0;

/// GLM mandates that the mat2, mat3, and mat4 constructors use column major order.
/// See: https://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf section 5.4 "Constructors"
/// The 2x2 identity Matrix 
const glm::mat2 MATRIX_IDENTITY_2D = glm::mat2{
	1, 0,
	0, 1
};
/// The 3x3 identity Matrix 
const glm::mat3 MATRIX_IDENTITY_3D = glm::mat3{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};
/// The 4x4 identity Matrix 
const glm::mat4 MATRIX_IDENTITY_4D = glm::mat4{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};
/// A 3x3 Matrix that will reflect a 2D point on the X axis. 
const glm::mat3 MATRIX_REFLECT_X_AXIS_2D = glm::mat3{
	1,  0, 0,
	0, -1, 0,
	0,  0, 1
};
/// A 3x3 Matrix that will reflect a 2D point on the Y axis. 
const glm::mat3 MATRIX_REFLECT_Y_AXIS_2D = glm::mat3{
	-1, 0, 0,
	 0, 1, 0,
	 0, 0, 1
};
/// A 3x3 Matrix that will reflect a 2D point along the line y=x 
const glm::mat3 MATRIX_REFLECTION_LINE_Y_EQUALS_X_2D = glm::mat3{
	0, 1, 0,
	1, 0, 0,
	0, 0, 1
};
/// A 3x3 Matrix that will cause a reflection along the line y=-x for a 2D point
const glm::mat3 MATRIX_REFLECT_LINE_Y_EQUALS_NEGX_2D = glm::mat3{
	 0, -1, 0,
	-1,  0, 0,
	 0,  0, 1
};


///
/// Non-inline functions.
///
glm::mat4x4 createLookAtMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

///
/// Inline functions
///
inline double rad(double deg)
{
	return deg / (180.0 / PI_D);
}

inline float rad(float deg)
{
	return deg / (180.0f / PI);
}

inline double deg(double rad)
{
	return rad * (180.0 / PI_D);
}

inline float deg(float rad)
{
	return rad * (180.0f / PI);
}

template <class T>
inline float square(T val)
{
	return val * val;
}

template <class T>
inline float cube(T val)
{
	return val * val * val;
}

///
/// Checks if two floats are approximately equal. This is done by seeing if the floats are within 1E-6 of each other.
/// \param a the first float to check for approximate equality
/// \param b the second float to check for approximate equality
/// \return a boolean, true, if the numbers are reasonably close together; otherwise false
///
/// @TODO -- verify this is working as intended
inline bool approximatelyEqual(float a, float b)
{
	return (fabs(a - b) < 0.00001f) ? true : false;
}

inline float clamp(float val, float min = 0.0f, float max = 1.0f)
{
	return (val < min) ? min : (val > max) ? max : val;
}

///
/// Rounds a float to the second decimal place.
///
inline float round2(float val)
{
	return roundf(val * 100.0f) / 100.0f;
}

/// 
/// Checks to see if a vector is parallel to another vector; which is to say that the vectors share a direction.
/// \return a bool - true if the vector provided are parallel, or false in all other cases
/// 
template<class T>
inline bool parallel(const T &v1, const T &v2)
{
	T thisAsUnitVector = glm::normalize(v1);
	T vUnitVector = glm::normalize(v2);
	T vCopy = vUnitVector * -1.0f;
	return thisAsUnitVector == vCopy || thisAsUnitVector == vUnitVector;
}

/// 
/// Checks to see if two vectors are perpendicular.
/// 
template<class T>
inline bool perpendicular(const T &v1, const T &v2)
{
	return approximatelyEqual(glm::dot(v1, v2), 0);
}

///
/// Projects the first vector u onto the second vector v. 
/// \return the vector which results from projecting u onto v
/// @TODO test this
///
template<class T>
inline T project(const T &u, const T &v)
{
	//Uses the following formula to project u onto v:
	//u dot v
	//-------  v = u projected onto v
	//v dot v
	//
	return v * (glm::dot(u, v) / glm::dot(v, v));
}

///
/// Gets the angle between the vectors u and v. This yields an angle in radians following the
/// same return rules as acos(float). 
/// \param u a vector
/// \param v a vector
/// \return a float indicating the angle between the vectors u and v, in radians
///
template<class T>
inline float angleBetween(const T &u, const T &v)
{
	float top = u.dot(v);
	float bottom = u.length() * v.length();
	return acos(top / bottom);
}

///
/// Rotates the provided vec2 around the origin by the specified number of degrees. 
/// \param v a vec2 to rotate around the origin. Not modified in the calculation.
/// \param angle a float indicating the angle of rotation in radians. If this value is positive
/// the rotation will be counter-clockwise, while a negative value will rotate clockwise
/// \return a vec2 which has the result of the rotation.
///
inline glm::vec2 rotateVec2OnOrigin(const glm::vec2 &v, float angle)
{
	float s = sin(angle);
	float c = cos(angle);
	// rotate point by inlining the 2D rotation matrix
	float xnew = v.x * c - v.y * s;
	float ynew = v.x * s + v.y * c;
	return glm::vec2(xnew, ynew);
}

///
/// Determines the angle between the line segments going from sharedPoint->lineSegment1Point and
/// sharedPoint->lineSegment2Point. 
/// \param sharedPoint a vec2 that is shared by both LineSegment2
/// \param lineSegment1Point a vec2 that is the "head" of the first LineSegment2, with a "tail" of the sharedPoint
/// \param lineSegment2Point a vec2 that is the "head" of the second LineSegment2, with a "tail" of the sharedPoint
/// \return a float which indicates the angle between the formed line segments, in radians. This will be an absolute value and in the interval [0, PI]
/// 
inline float angleOfConnectedLineSegments(glm::vec2 sharedPoint, glm::vec2 lineSegment1Point, glm::vec2 lineSegment2Point)
{
	//Uses the Law of Cosines, which is:
	//c^2 = a^2 + b^2 - 2ab * cosC rearranged to
	//arccos((c^2 - b^2 - a^2) / -2ab) = C
	LineSegment2 a(sharedPoint, lineSegment1Point);
	LineSegment2 b(sharedPoint, lineSegment2Point);
	LineSegment2 c(lineSegment1Point, lineSegment2Point);
	float lenA = a.length();
	float lenB = b.length();
	float lenC = c.length();
	return acos((lenC*lenC - lenB*lenB - lenA*lenA) / (-2 * lenA * lenB));
}

///
/// Converts polar co-ordinates(magnitudes, radians) to rectangular (x,y).
/// \param magnitude magnitude of the vector
/// \param angle the radian value to convert using
/// \return a vec2 which contains the rectangular co-ordinates 
///
inline glm::vec2 toRectangular(float magnitude, float angle)
{
	return glm::vec2(magnitude * cos(angle), magnitude * sin(angle));
}

///
/// Constructs a rotation matrix, to rotate a point in 2D around the origin. The Matrix result will be a matrix in the form: 
/// |cos(angle) -sin(angle) 0|
/// |sin(angle)  cos(angle) 0|
/// |0           0          1|
/// \param angle a float which is the angle of rotation in radians
/// \return a mat3, which will rotate a point around the origin the specified number of degrees
/// 
inline glm::mat3 construct2DRotationMatrix(float angle)
{
	return glm::mat3(
		cos(angle), -sin(angle), 0,
		sin(angle),  cos(angle), 0,
				 0,	     	  0, 1
	);
}

///
/// Constructs a translation matrix, to translate a point in 2d. the Matrix result will be a matrix in the form: 
/// |1 0 x| 
/// |0 1 y| 
/// |0 0 1|
/// \param x a float which is the x-translation
/// \param y a float which is the y-translation
/// \return a mat3, which will translate a point the specified amounts.
/// 
inline glm::mat3 construct2DTranslationMatrix(float x, float y)
{
	return glm::mat3(
		1, 0, x,
		0, 1, y,
		0, 0, 1
	);
}

///
/// Constructs a scaling matrix, to scale a point in 2d. The Matrix result will be a matrix in the form: 
/// |x 0 0|
/// |0 y 0|
/// |0 0 1|
/// \param x a float, which is the horizontal scaling factor
/// \param y a float, which is the vertical scaling factor
/// \return a mat3, which will scale a point the specified amounts.
///
inline glm::mat3 construct2DScalingMatrix(float x, float y)
{
	return glm::mat3(
		x, 0, 0,
		0, y, 0,
		0, 0, 1
	);
}

///
/// Constructs a scaling matrix, to scale a point in 3d. The Matrix result will be a matrix in the form: 
/// |x 0 0 0|
/// |0 y 0 0|
/// |0 0 z 0|
/// |0 0 0 1|
/// \param x a float, which is the horizontal scaling factor
/// \param y a float, which is the vertical scaling factor
/// \param z a float, which is the depth scaling factor
/// \return a glm::mat4, which will scale a point the specified amounts.
///
inline glm::mat4 construct3DScalingMatrix(float x, float y, float z)
{
	return glm::mat4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1 
	);
}

///
/// Constructs a translation matrix, to translate a point in 3d. The Matrix result will be a matrix in the form: 
/// |1 0 0 x|
/// |0 1 0 y|
/// |0 0 1 z|
/// |0 0 0 1|
/// \param x a float, which is the horizontal translation
/// \param y a float, which is the vertical translation
/// \param z a float, which is the depth translation
/// \return a glm::mat4, which will translate a point the specified amounts.
///
inline glm::mat4 construct3DTranslationMatrix(float x, float y, float z)
{
	return glm::mat4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}

///
/// Constructs a rotation matrix, to rotate a point in 3D around the X-axis relative to the origin.
/// The Matrix result will be a matrix in the form: 
/// |1 0           0          0|
/// |0 cos(angle) -sin(angle) 0|
/// |0 sin(angle)  cos(angle) 0|
/// |0 0           0          1|
/// \param angle a float which is the angle of rotation in radians
/// \return a glm::mat4 which will rotate a point around the X-axis the given amount relative to the origin.	 
///
inline glm::mat4 construct3dRotationMatrixOnX(float angle)
{
	return glm::mat4(
		1, 0,			0,			0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle),  cos(angle), 0,
		0, 0,			0,			1
	);
}

///
/// Constructs a rotation matrix, to rotate a point in 3D around the Y-axis relative to the origin.
/// The Matrix result will be a matrix in the form: 
/// |cos(angle)  0 sin(angle) 0|
/// |0           1 0          0|
/// |-sin(angle) 0 cos(angle) 0|
/// |0           0 0          1|
/// \param angle a float which is the angle of rotation in radians
/// \return a mat4 which will rotate a point around the Y-axis the given amount relative to the origin.	 
///
inline glm::mat4 construct3dRotationMatrixOnY(float angle)
{
	return glm::mat4(
		cos(angle),  0, sin(angle), 0,
		0,			 1, 0,			0,
		-sin(angle), 0, cos(angle), 0,
		0,			 0, 0,			1 
	);
}

///
/// Constructs a rotation matrix, to rotate a point in 3D around the Z-axis relative to the origin.
/// The Matrix result will be a matrix in the form: 
/// |cos(angle) -sin(angle) 0 0|
/// |sin(angle)  cos(angle) 0 0|
/// |0           0          1 0|
/// |0           0          0 1|
/// \param angle a float which is the angle of rotation in radians
/// \return a Matrix which will rotate a point around the Z-axis the given amount relative to the origin.	 
///
inline glm::mat4 construct3dRotationMatrixOnZ(float angle)
{
	return glm::mat4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle),  cos(angle), 0, 0,
		0,			 0,			 1, 0,
		0,			 0,			 0, 1
	);
}

#endif

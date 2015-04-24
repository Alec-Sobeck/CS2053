#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include "math/intersection.h"

const float PI = 3.14159265359f;
const double PI_D = 3.14159265359;
const float PIOVER2 = 3.14159265359f / 2.0f;
const double PIOVER2_D = 3.14159265359 / 2.0;

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
/// 
/// Checks to see if a vector is parallel to another, which is to say that the vectors share a direction.
/// \return a bool - true if the Vectors are parallel, or false otherwise
/// 
bool parallel(glm::vec3, glm::vec3);
/// 
/// Checks to see if two vectors are perpendicular.
/// 
bool perpendicular(glm::vec3, glm::vec3);

inline float clamp(float val, float min = 0.0f, float max = 1.0f)
{
	return (val < min) ? min : (val > max) ? max : val;
}

inline float round2(float val)
{
	return roundf(val * 100) / 100;
}

glm::mat4x4 createLookAtMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

#endif

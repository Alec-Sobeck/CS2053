#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

const float PI = 3.14159265359f;
const double PI_D = 3.14159265359;

const float PI_2 = 3.14159265359f / 2.0f;
const double PI_2_D = 3.14159265359 / 2;

double toRad(double deg);
float  toRad(float deg);
double toRad(int deg);
double toDeg(double rad);
float  toDeg(float rad);
double toDeg(int rad);

inline float square(float val)
{
	return val * val;
}

inline float cube(float val)
{
	return val * val * val;
}

inline double square(double val)
{
	return val * val;
}

inline double cube(double val)
{
	return val * val * val;
}
/// 
/// Checks if two floats are approximately equal. This is done by seeing if the floats are within 1E-6 of each other.
/// \param a the first float to check for approximate equality
/// \param b the second float to check for approximate equality
/// \return a boolean, true, if the numbers are reasonably close together; otherwise false
/// 
bool approximatelyEqual(float, float);

/// 
/// Checks to see if a vector is parallel to another, which is to say that the vectors share a direction.
/// \return a boolean, true if the Vectors are parallel, or false otherwise
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

float round2(float val);
glm::mat4x4 createLookAtMatrix(glm::vec3 eye, glm::vec3 target, glm::vec3 up);


#endif

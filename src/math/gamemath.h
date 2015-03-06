#ifndef GAMEMATH_H
#define GAMEMATH_H

#include <glm/vec3.hpp>

const float PI = 3.14159265359f;
const double PI_D = 3.14159265359;

double toRad(double deg);
float  toRad(float deg);
double toRad(int deg);
double toDeg(double rad);
float  toDeg(float rad);
double toDeg(int rad);

/**
 * Checks if two floats are approximately equal. This is done by seeing if the floats are within
 * 1E-6 of each other.
 * @param a the first float to check for approximate equality
 * @param b the second float to check for approximate equality
 * @return a boolean, true, if the numbers are reasonably close together; otherwise false
*/

bool approximatelyEqual(float, float);

/**
* Checks to see if a Vector is parallel to another, which is to say that the vectors share a direction.
* @return a boolean, true if the Vectors are parallel, or false otherwise
*/
bool parallel(glm::vec3, glm::vec3);
/**
* Checks to see if two Vectors are perpendicular.
*/
bool perpendicular(glm::vec3, glm::vec3);

float clamp(float val);

float round2(float val);

#endif

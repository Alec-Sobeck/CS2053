/**
 * A collection of interpolation methods. Undefined if given a progress < 0 or > 1
 * @author Matthew Robertson
 */
#ifndef INTERPOLATORS_H
#define INTERPOLATORS_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

/**
 * Lerps between value a and value b. Returns a value based on t.
 * @param a first value
 * @param b the second value
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return
 */
double linearInterpolate(double a, double b, double t);
/**
 * Lerps between two glm::vec2s a and b. Based on t
 * @param a the first glm::vec2
 * @param b the second glm::vec2
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return a glm::vec2
 */
glm::vec2 linearInterpolate(glm::vec2 a, glm::vec2 b, double t);
/**
 * Lerps between two glm::vec3s a and b. Based on t
 * @param a the first glm::vec3
 * @param b the second glm::vec3
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return a glm::vec3
 */
glm::vec3 linearInterpolate(glm::vec3 a, glm::vec3 b, double t);
/**
 * Bilinearly interpolates between values p00, p01, p10, and p11 Visualized as:
 * p00 - - - - p10
 *  |    .      |
 *  |           |
 * p10 - - - - p11
 * @param p00
 * @param p01
 * @param p10
 * @param p11
 * @param tx a double, between 0 and 1, representing progress from p00 to p01 (and p10 to p11)
 * @param ty a double, between 0 and 1, representing progress from p00 to p10 (and p01 to p11)
 * @return
 */
double bilinearInterpolate(double p00, double p01, double p10, double p11, double tx, double ty);

/**
 * Interpolate between value a and value b more smoothly than lerping. Returns a value based on t.
 * @param a first value
 * @param b the second value
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return
 */
double cosineInterpolate(double a, double b, double t);
/**
 * cosine interpolates between values p00, p01, p10, and p11 Visualized as:
 * p00 - - - - p10
 *  |    .      |
 *  |           |
 * p10 - - - - p11
 * @param p00
 * @param p01
 * @param p10
 * @param p11
 * @param tx a double, between 0 and 1, representing progress from p00 to p01 (and p10 to p11)
 * @param ty a double, between 0 and 1, representing progress from p00 to p10 (and p01 to p11)
 * @return
 */
double bicosineInterpolate(double p00, double p01, double p10, double p11,  double tx, double ty);
/**
 * Interpolates between b and c smoothly.
 * @param a the value before b
 * @param b the first value
 * @param c the second value
 * @param d the value after c
 * @param t a double, between 0 and 1, representing percentage traveled from b to c
 * @return
 */
double cubicInterpolate(double a, double b, double c, double d, double t);
/**
 * Interpolates between two glm::vec2s a and b. Based on t
 * @param a the value before b
 * @param b the first value
 * @param c the second value
 * @param d the value after c
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return a glm::vec2
 */
glm::vec2 CubicInterpolate(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, double t);
/**
 * Interpolates between two glm::vec3s a and b. Based on t
 * @param a the value before b
 * @param b the first value
 * @param c the second value
 * @param d the value after c
 * @param t a double, between 0 and 1, representing percentage traveled from a to b
 * @return a glm::vec3
 */
glm::vec3 CubicInterpolate(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, double t);


#endif

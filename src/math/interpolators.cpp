
#include <cmath>
#include "math/gamemath.h"
#include "math/interpolators.h"

double linearInterpolate(double a, double b, double t)
{
    return(a*(1-t) + b*t);
}

glm::vec2 linearInterpolate(glm::vec2 a, glm::vec2 b, double t)
{
    return glm::vec2(linearInterpolate(a.x, b.x, t), linearInterpolate(a.y, b.y, t));
}

glm::vec3 linearInterpolate(glm::vec3 a, glm::vec3 b, double t)
{
    return glm::vec3(linearInterpolate(a.x, b.x, t),
                     linearInterpolate(a.y, b.y, t),
                     linearInterpolate(a.z, b.z, t));
}

double bilinearInterpolate(double p00, double p01, double p10, double p11, double tx, double ty)
{
    return linearInterpolate(linearInterpolate(p00, p01, tx), linearInterpolate(p10, p11, tx), ty);
}

double cosineInterpolate(double a, double b, double t)
{
   double prog2 = (1-cos(t*PI))/2;
   return(a*(1-prog2) + b*prog2);
}

double bicosineInterpolate(double p00, double p01, double p10, double p11,  double tx, double ty)
{
    return cosineInterpolate(cosineInterpolate(p00, p01, tx), cosineInterpolate(p10, p11, tx), ty);
}

double cubicInterpolate(double a, double b, double c, double d, double t)
{
    double prog2 = t*t;
    double a0 = d - c - a + b;
    double a1 = a - b - a0;
    double a2 = c - a;
    double a3 = b;

   return(a0*t*prog2 + a1*prog2 + a2*t + a3);
}

glm::vec2 CubicInterpolate(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, double t)
{
    return glm::vec2(cubicInterpolate(a.x, b.x, c.x, d.x, t),
                     cubicInterpolate(a.y, b.y, c.y, d.y, t));
}

glm::vec3 CubicInterpolate(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, double t)
{
    return glm::vec3(cubicInterpolate(a.x, b.x, c.x, d.x, t),
                     cubicInterpolate(a.y, b.y, c.y, d.y, t),
                     cubicInterpolate(a.z, b.z, c.z, d.z, t));
}

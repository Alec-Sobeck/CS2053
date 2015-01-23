
#include <cmath>
#include "gamemath.h"


double toRad(double deg)
{
    return deg / (180.0 / PI_D);
}

float toRad(float deg)
{
    return deg / (180.0f / PI);
}

double toRad(int deg)
{
    return static_cast<double>(deg) / (180.0f / PI_D);
}

double toDeg(double rad)
{
    return rad * (180.0 / PI_D);
}

float toDeg(float rad)
{
    return rad * (180.0f / PI);
}

double toDeg(int rad)
{
    return static_cast<double>(rad) * (180.0 / PI_D);
}

// TODO -- verify this is working as intended
bool approximatelyEqual(float a, float b)
{
    return ((a - b) < 0.00001 && (a - b) > -0.00001) ? true : false;
}


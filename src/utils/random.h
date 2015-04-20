#ifndef UTILS_RANDOM_H
#define UTILS_RANDOM_H


///
/// Seeds the random number generator with the system time. This will only seed the random number generator the first time it's called; doing nothing on
/// subsequent calls.
///
void seedRandomGenerator();
///
/// Generates a pseudo random integer value from somewhere in the range from 0 to (maxValue - 1).
/// \return a pseudo-random number from 0 to (maxValue - 1) inclusive.
///
int getRandomInt(int maxValue);
///
/// Generates a float value from 0 to 1 inclusive.
///
float getRandomFloat();


#endif

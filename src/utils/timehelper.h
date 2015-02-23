#ifndef ENGINE_TIME_HELPER_H
#define ENGINE_TIME_HELPER_H

/**
 * Gets the current time since the linux epoch, in milliseconds. Return type is an
 * unsigned long long to ensure enough bits of precision in the returned value.
 * @return unsigned long long
 */
unsigned long long getCurrentTimeMillis();


#endif

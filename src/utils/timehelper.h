#pragma once

///
/// Gets the current time since the linux epoch, in milliseconds. Return type is an
/// unsigned long long to ensure enough bits of precision in the returned value.
///
unsigned long long getCurrentTimeMillis();


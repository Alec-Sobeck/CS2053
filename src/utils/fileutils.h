#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

/**
 * Reads the contents of a text file into a std::string. Throws std::runtime_error if the file fails to open.
 */
std::string readTextFile(std::string filepath);
/**
 * Writes the contents of an std::string to fail. Throws std::runtime_error if the file fails to open.
 */
void writeTextFile(std::string filepath, std::string contents);

#endif // FILEUTILS_H

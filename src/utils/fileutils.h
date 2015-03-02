#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>

/**
 * Reads the contents of a text file into a std::string. Throws std::runtime_error if the file fails to open.
 */
std::string readTextFile(std::string filepath);
/**
 * Writes the contents of an std::string to fail. Throws std::runtime_error if the file fails to open.
 */
void writeTextFile(std::string filepath, std::string contents);
/**
 * Reads the contents of a text file, adding each line as a separate string in a vector.
 */
std::vector<std::string> readTextFileAsLines(std::string filepath);

#endif // FILEUTILS_H

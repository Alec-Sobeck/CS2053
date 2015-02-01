#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

std::string readTextFile(std::string filepath);
void writeTextFile(std::string filepath, std::string contents);

#endif // FILEUTILS_H

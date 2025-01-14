#ifndef ENGINE_MISC_H
#define ENGINE_MISC_H

#include <string>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
double parseDouble(const std::string& s);

#endif


#include <string>
#include <fstream>
#include <sstream>
#include "fileutils.h"

std::string readTextFile(std::string filepath)
{
    std::ifstream infile(filepath.c_str());
    std::string line;
    std::stringstream content;
    while (std::getline(infile, line))
    {
        content << line << "\n";
    }
    return content.str();
}

void writeTextFile(std::string filepath, std::string contents)
{
    std::ofstream file(filepath.c_str());
    file << contents;
    file.close();
}

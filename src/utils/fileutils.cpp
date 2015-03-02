
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "fileutils.h"

std::string readTextFile(std::string filepath)
{
    std::ifstream infile(filepath.c_str());
    if(infile.fail())
    {
        std::stringstream ss;
        ss << "Failure to open file at " << filepath;
        throw std::runtime_error(ss.str());
    }
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
    if(file.fail())
    {
        std::stringstream ss;
        ss << "Failure to open file at " << filepath;
        throw std::runtime_error(ss.str());
    }
    file << contents;
    file.close();
}

std::vector<std::string> readTextFileAsLines(std::string filepath)
{
    std::vector<std::string> out;
    std::ifstream infile(filepath.c_str());
    if(infile.fail())
    {
        std::stringstream ss;
        ss << "Failure to open file at " << filepath;
        throw std::runtime_error(ss.str());
    }
    std::string line;
    while (std::getline(infile, line))
    {
        out.push_back(line);
    }
    return out;
}

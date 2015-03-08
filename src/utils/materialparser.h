#ifndef MATERIAL_PARSER_H
#define MATERIAL_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <glm/vec3.hpp>
#include "world/material.h"

class MaterialParser
{
public:
    std::vector<std::string> fileContents;
    MaterialParser(std::vector<std::string> &fileContents);
    std::map<std::string, std::shared_ptr<Material>> parseMaterials();
};

#endif

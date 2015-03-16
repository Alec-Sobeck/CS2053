
#include "utils/materialparser.h"
#include "world/material.h"
#include "utils/misc.h"

MaterialParser::MaterialParser(std::vector<std::string> &fileContents)
    : fileContents(fileContents)
{

}

std::map<std::string, std::shared_ptr<Material>> MaterialParser::parseMaterials()
{
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::string line;

    bool hasEncounteredNewMaterial = false;
    std::string materialName = "null";
    glm::vec3 ambientColour(0, 0, 0); /// Ka field
	glm::vec3 diffuseColour(0, 0, 0); /// Kd field
	glm::vec3 specularColour(0, 0, 0); /// Ks field
    float specularPower; ///Ns field
	float d = 0.0f; /// d field
    float Tr = 0.0f; /// Tr field
    float illum = 0.0f;

    for(unsigned int i = 0; i < fileContents.size(); i++)
    {
        line = fileContents[i];
        std::vector<std::string> splitLine = split(line, ' ');
        if(line.find("#") == 0)
        {
            continue;
        }
        else if(line.find("newmtl ") == 0)
        {
            if(hasEncounteredNewMaterial)
            {
                materials[materialName] = std::shared_ptr<Material>(new Material(materialName, ambientColour, diffuseColour, specularColour,
                    specularPower, d, Tr, illum
                ));
            }
            hasEncounteredNewMaterial = true;
            materialName = splitLine.at(1);
        }
        else if (line.find("Ka ") == 0)
        {
            ambientColour = glm::vec3(parseDouble(splitLine.at(1)), parseDouble(splitLine.at(2)), parseDouble(splitLine.at(3)));
        }
        else if (line.find("Kd ") == 0)
        {
            diffuseColour = glm::vec3(parseDouble(splitLine.at(1)), parseDouble(splitLine.at(2)), parseDouble(splitLine.at(3)));
        }
        else if (line.find("Ks ") == 0)
        {
            specularColour = glm::vec3(parseDouble(splitLine.at(1)), parseDouble(splitLine.at(2)), parseDouble(splitLine.at(3)));
        }
        else if (line.find("Ns ") == 0)
        {
            specularPower = parseDouble(splitLine.at(1));
        }
        else if (line.find("d ") == 0)
        {
            d = parseDouble(splitLine.at(1));
        }
        else if (line.find("Tr ") == 0)
        {
            Tr = parseDouble(splitLine.at(1));
        }
        else if (line.find("illum ") == 0)
        {
            illum = parseDouble(splitLine.at(1));
        }
    }
    if(hasEncounteredNewMaterial)
    {
        materials[materialName] = std::shared_ptr<Material>(new Material(materialName, ambientColour, diffuseColour, specularColour,
            specularPower, d, Tr, illum
        ));
    }
    return materials;
}



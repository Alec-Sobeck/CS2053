#include "world/material.h"


Material::Material(std::string name, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour, float specularPower, float d, float Tr,
    int illum)
: materialName(name), ambientColour(ambientColour), diffuseColour(diffuseColour), specularColour(specularColour), specularPower(specularPower), d(d), Tr(Tr),
    illum(illum)
{

}

void Material::applyGLSettings()
{
    /// Well, this should do something. We don't have lighting yet though.
}

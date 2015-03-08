#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <string>
#include <glm/vec3.hpp>

class Material
{
public:
    ///
    /// Multiple illumination models are available, per material. These are enumerated as follows:
    ///
    /// 0. Color on and Ambient off
    const static int ILLUMINATION_0 = 0;
    /// 1. Color on and Ambient on
    const static int ILLUMINATION_1 = 1;
    /// 2. Highlight on
    const static int ILLUMINATION_2 = 2;
    /// 3. Reflection on and Ray trace on
    const static int ILLUMINATION_3 = 3;
    /// 4. Transparency: Glass on, Reflection: Ray trace on
    const static int ILLUMINATION_4 = 4;
    /// 5. Reflection: Fresnel on and Ray trace on
    const static int ILLUMINATION_5 = 5;
    /// 6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
    const static int ILLUMINATION_6 = 6;
    /// 7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
    const static int ILLUMINATION_7 = 7;
    /// 8. Reflection on and Ray trace off
    const static int ILLUMINATION_8 = 8;
    /// 9. Transparency: Glass on, Reflection: Ray trace off
    const static int ILLUMINATION_9 = 9;
    /// 10. Casts shadows onto invisible surfaces
    const static int ILLUMINATION_10 = 10;
    std::string materialName;
    glm::vec3 ambientColour; /// Ka field
    glm::vec3 diffuseColour; /// Kd field
    glm::vec3 specularColour; /// Ks field
    float specularPower; ///Ns field
    float d; /// d field
    float Tr; /// Tr field
    int illum;
    Material(std::string name, glm::vec3 ambientColour, glm::vec3 diffuseColour, glm::vec3 specularColour, float specularPower, float d, float Tr, int illum);
    void applyGLSettings();
};

#endif

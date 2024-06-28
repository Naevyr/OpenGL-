#pragma once
#include <string>

struct MaterialDefinition {
    
    std::string albedoPath = "resources/textures/default-albedo.png";
    std::string normalPath = "resources/textures/default-normal.png";
    std::string roughnessPath = "resources/textures/default-roughness.png";
    std::string specularPath = "resources/textures/default-specular.png";
    std::string emissivePath = "resources/textures/default-emissive.png";


    bool lightingEnabled = false;
};
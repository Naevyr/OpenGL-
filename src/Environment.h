#pragma once
#include <glm/glm.hpp>
#include <string>


struct EnvironmentDescription
{   
    
    std::string skyboxPath = "/resources/textures/skybox";
    glm::vec3 globalIllumination = glm::vec3(1.0, 1.0, 1.0);
    float globalIlluminationIntensity = 1;
    Mesh skybox = Mesh("resources/3D/cube.obj",0);


    struct PostProcessingEffects
    {
        bool bloom = false;
    };
    PostProcessingEffects effects;
    
};
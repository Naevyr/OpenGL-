#pragma once
#include <glm/glm.hpp>
#include <string>


struct Environment
{   
    
    std::string skyboxPath = "/resources/textures/skybox";
    glm::vec3 globalIllumination = glm::vec3(1.0, 1.0, 1.0);
    float globalIlluminationIntensity = 1;
    Mesh skybox = Mesh("resources/3D/cube.obj",0);
    
};
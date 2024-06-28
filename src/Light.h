#pragma once
#include <glm/glm.hpp>



enum LightType
{
    POINT = 0,
    DIRECTIONAL = 1
};


struct Light
{
    glm::mat4 lightSpaceMatrix;
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction;
    float intensity;
    LightType type;
};

struct LightUniform {
    unsigned int count;
    int padding[3];
    Light lights[20];
};
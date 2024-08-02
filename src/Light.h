#pragma once
#include <glm/glm.hpp>



enum LightType
{
    POINT = 0,
    DIRECTIONAL = 1,
    SPOT = 2
};


struct Light
{
    glm::mat4 lightSpaceMatrix;
    glm::vec3 position;
    float _padding1;
    glm::vec3 color;
    float _padding2;
    glm::vec3 direction;
    float intensity;

    LightType type;

    int _padding3[3];
};

struct LightUniform {
    unsigned int count;
    int padding[3];
    Light lights[20];
};
#pragma once
#include <glm/glm.hpp>

struct LightDescription
{   

    enum LightType
    {
        POINT = 0,
        DIRECTIONAL = 1,
        SPOT = 2
    };

    LightType type;
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};
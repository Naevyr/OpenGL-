#pragma once
#include <glm/glm.hpp>



enum LightType
{
    POINT = 0,
    DIRECTIONAL = 1,
    SPOT = 2
};


class Light : public Node
{
    private: 
        glm::vec3 m_color;
        float m_intensity;
        LightType m_type;
    public:
        Light();
        
        void setColor(glm::vec3 color);
        glm::vec3 getColor();
        void setIntensity(float intensity);
        float getIntensity();
        void setType(LightType type);
        LightType getType();

        LightUniform getUniformStruct();
};


struct LightUniform {
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
struct LightUniformBuffer {
    unsigned int count;
    int padding[3];
    Light lights[20];
};
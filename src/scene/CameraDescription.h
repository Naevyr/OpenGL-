#pragma once

#include <glm/glm.hpp>



class CameraDescription 
{

    glm::vec3 m_position;
    float m_fov = 45.0f;
    float m_pitch = 0;
    float m_yaw = 0;



    bool m_speeding = false;


    void movementInput(glm::vec3 direction, float delta);
    void rotationInput(glm::vec2 movement, float delta);

};
#pragma once
#include "scene/CameraDescription.h"
#include <glm/gtc/quaternion.hpp>
#include "Node.h"


class Camera : public Node
{
    private:
    
        float m_fov = 45.0f;
        float m_pitch = 0;
        float m_yaw = 0;
        bool m_speeding = false;
    
    public:
        Camera();
        glm::mat4 getOrientation() const;
        void movementInput(glm::vec3 direction, float delta);
        void rotationInput(glm::vec2 rotation, float delta);
};
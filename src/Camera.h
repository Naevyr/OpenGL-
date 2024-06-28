#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>



class Camera {
    private:
        glm::vec3 m_position;
        float m_fov = 45.0f;
        float m_pitch = 0;
        float m_yaw = 0;



        bool m_speeding = false;
    
    public:
        Camera();

        void setPosition(glm::vec3 position)  { m_position = position; }

        void setOrientation(float pitch, float yaw) { m_pitch = pitch; m_yaw = yaw; }

        glm::vec3 getPosition() const { return m_position; }

        glm::mat4 getOrientation() const;
        

        inline bool isSpeeding() const { return m_speeding; }
        inline void setSpeeding(bool speeding) { m_speeding = speeding; }
        

        void movementInput(glm::vec3 direction, float delta);
        void rotationInput(glm::vec2 movement, float delta);
    
};
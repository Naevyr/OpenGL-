#pragma once
#include "scene/CameraDescription.h"
#include <glm/gtc/quaternion.hpp>

class Camera : public CameraDescription
{
    public:
        Camera();
        glm::mat4 getOrientation() const;
};
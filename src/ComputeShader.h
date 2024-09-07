#pragma once
#include "Program.h"
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class ComputeShader : public Program {
     
    public:
        inline ComputeShader() {}
        ComputeShader(std::string path);
        void Dispatch(glm::ivec3 axis);
        

     
        void SetTexture(std::string name, Texture& texture, unsigned int usage, unsigned int mipmap = 0);
};
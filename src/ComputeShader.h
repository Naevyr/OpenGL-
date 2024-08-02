#pragma once
#include "Program.h"
#include <string>



class ComputeShader : public Program {
     
    public:
        inline ComputeShader() {}
        ComputeShader(std::string path);
        void Dispatch(glm::ivec3 axis);


        void SetTexture(unsigned int unit, Texture& texture);
    
        void SetTexture(unsigned int unit, Texture& texture, int mipmap, unsigned int usage, std::string samplerName = "");
};
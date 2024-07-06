#pragma once
#include "Program.h"
#include <string>



class ComputeShader : public Program {
     
    public:
        inline ComputeShader() {}
        ComputeShader(std::string path);

        void Dispatch(glm::ivec3 axises);
};
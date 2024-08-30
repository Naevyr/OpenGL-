#pragma once

#include "Program.h"
#include "Texture.h"

#include <glad/glad.h>


#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

typedef unsigned int MaterialHandle;

class Material : public Program {
   

    protected:
        void BindProgram();
    public:
        inline Material() {}
        Material(std::string vertexPath, std::string fragmentPath);

        inline unsigned int getProgram() { return m_programID; }

};


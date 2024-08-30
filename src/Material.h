#pragma once

#include "Program.h"
#include "Texture.h"

#include <glad/glad.h>


#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>




class Material : public Program {
   

    protected:
    
    
        bool m_lightingEnabled = false;
    protected:
        void BindProgram();
    public:
        inline Material() {}
        Material(std::string vertexPath, std::string fragmentPath);


      
        inline unsigned int GetProgram() { return m_programID; }

        inline bool GetLightingFlag() { return m_lightingEnabled; }
        inline void SetLightingFlag(bool enabled) { m_lightingEnabled = enabled; }


};


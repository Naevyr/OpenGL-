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
    
        std::unordered_map<std::string, std::reference_wrapper<Texture>> m_textures;
        bool m_lightingEnabled = false;
    protected:
        void BindProgram();
    public:
        inline Material() {}
        Material(const char * vertexPath, const char * fragmentPath);
        
        
        void Use();

        inline void SetTexture(std::string name, Texture &texture ) { m_textures.insert({name,texture}); }
        
        inline size_t GetTextureCount() { return m_textures.size(); }
        inline unsigned int GetProgram() { return m_programID; }

        inline bool GetLightingFlag() { return m_lightingEnabled; }
        inline void SetLightingFlag(bool enabled) { m_lightingEnabled = enabled; }

};

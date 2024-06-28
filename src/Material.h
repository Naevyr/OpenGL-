#pragma once

#include "Program.h"
#include "Texture.h"

#include <glad/glad.h>


#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

class Material {
   

    protected:
        unsigned int m_programID;
        std::unordered_map<std::string, std::reference_wrapper<Texture>> m_textures;
    


        bool m_lightingEnabled = false;
    protected:
        void BindProgram();
    public:
        inline Material() {}
        Material(const char * vertexPath, const char * fragmentPath);
        
        
        void Use();
        void Bind();
        inline void SetTexture(std::string name, Texture &texture ) { m_textures.insert({name,texture}); }
        
        inline size_t GetTextureCount() { return m_textures.size(); }
        inline unsigned int GetProgram() { return m_programID; }

        inline bool GetLightingFlag() { return m_lightingEnabled; }
        inline void SetLightingFlag(bool enabled) { m_lightingEnabled = enabled; }



        
        template <typename T>
        void SetUniform(std::string name, T value);
        
        template<>
        void SetUniform(std::string name, glm::mat4 value);

        template<>
        void SetUniform(std::string name, glm::vec4 value);

        template<>
        void SetUniform(std::string name, glm::vec3 value);

        template<>
        void SetUniform(std::string name, glm::vec2 value);

        template<>
        void SetUniform(std::string name, float value);

        template<>
        void SetUniform(std::string name, int value);

        void BindBlock(std::string name, unsigned int index);

};




template<>
void Material::SetUniform(std::string name, glm::mat4 value) {
    
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);

}


template<>
void Material::SetUniform(std::string name, glm::vec4 value) {

    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform4fv(location, 1, &value[0]);

}
template<>
void Material::SetUniform(std::string name, glm::vec3 value) {

    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform3fv(location, 1, &value[0]);

}


template<>
void Material::SetUniform(std::string name, glm::vec2 value) {

    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform2fv(location, 1, &value[0]);


}

template<>
void Material::SetUniform(std::string name, float value) {

    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(location, value );
}

template<>
void Material::SetUniform(std::string name, int value) {

    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1i(location, value );
}

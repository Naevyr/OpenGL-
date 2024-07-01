#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
class Program {
    protected:
        unsigned int m_programID;
        
    public:
        void Initialize();
        ~Program();


        void Bind();
        
        template <typename T>
        void SetUniform(std::string name, T value);
        
       /*  template<>
        void SetUniform<glm::mat4>(std::string name, glm::mat4 value);

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

 */
        void BindBlock(std::string name, unsigned int index);

};


template<>
void Program::SetUniform(std::string name, int value);
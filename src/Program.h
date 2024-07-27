#pragma once
#include <glm/glm.hpp>
#include "Texture.h"



class Program {
    protected:
        unsigned int m_programID;
        
    public:
        ~Program();


        void Initialize();
        void Bind();
        void BindBlock(std::string name, unsigned int index);
        template <typename T>
        void SetUniform(std::string name, T value);
        virtual void SetTexture(unsigned int unit, Texture& texture);

};


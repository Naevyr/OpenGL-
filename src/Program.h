#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include <unordered_map>
struct TextureBinding {
    std::string name;
    unsigned int unit;
    unsigned int textureID;
    unsigned int type;
    inline TextureBinding() {}
    inline TextureBinding(std::string name, unsigned int unit, unsigned int textureID, unsigned int type) : name(name), unit(unit), textureID(textureID), type(type) {}
};

class Program {
    private: 

       std::unordered_map<std::string,TextureBinding> m_textureUnits;


    protected:
        unsigned int m_programID;
        void SetTexture(std::string name, unsigned int unit, unsigned int type, unsigned int textureID);
    public:
        ~Program();


        void Initialize();
        void Bind();
        void BindBlock(std::string name, unsigned int index);
        template <typename T>
        void SetUniform(std::string name, T value);

};


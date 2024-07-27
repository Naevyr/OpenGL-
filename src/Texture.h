#pragma once
#include <string>
#include <array>
#include <glad/glad.h>
template <size_t N = 1>
struct LocalTextureSpecs {
   
    std::array<std::string, N> path = {"resources/textures/default-abledo.png"};
    unsigned int format = GL_RGBA;
    unsigned int internal_format = GL_RGBA;
    unsigned int encoding = GL_UNSIGNED_BYTE;
    unsigned int type = GL_TEXTURE_2D;

    unsigned int mipmap_levels = 1;

};


struct RuntimeTextureSpecs {
    int width = -1;
    int height = -1;
    int depth = 1;
    unsigned int wrapping = GL_CLAMP_TO_EDGE;
    unsigned int filtering = GL_LINEAR;
    unsigned int mipmap_levels = 1;
    
    unsigned int format = GL_RGBA;
    unsigned int internal_format = GL_RGBA;
    unsigned int encoding = GL_FLOAT;
    unsigned int type = GL_TEXTURE_2D;

};

struct VirtualTextureSpecs {
    int width = -1;
    int height = -1;
    int depth = 1;
    unsigned int handle = 0;    

    unsigned int format = GL_RGBA;
    unsigned int internal_format = GL_RGBA;
    unsigned int encoding = GL_FLOAT;
    unsigned int type = GL_TEXTURE_2D;
    
    unsigned int mipmap_levels = 1;
};

class Texture {
    private:
        unsigned int m_textureID;
        unsigned int m_textureType;
        
        unsigned int m_format;

        int m_width;
        int m_height;


        
    public:

        inline Texture() {}
        
        template <size_t N = 1>
        static Texture CreateTexture(LocalTextureSpecs<N> specs);
  
        static Texture CreateTexture(VirtualTextureSpecs specs);
        static Texture CreateTexture(RuntimeTextureSpecs specs);
        





        inline void Bind() { glBindTexture(m_textureType, m_textureID); } 
        void Use(unsigned int unit) const;

        
        inline unsigned int GetTextureID() const { return m_textureID; }
        inline int GetWidth() const  { return m_width; }
        inline int GetHeight() const { return m_height; } 
        inline unsigned int GetFormat() const {return m_format; }   

        void TargetMipMap(unsigned int level);
        

};

#include "Texture.inl"
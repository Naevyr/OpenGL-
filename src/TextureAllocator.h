#pragma once
#include <glad/glad.h>
#include <map>
#include "Texture.h"


typedef unsigned int TextureHandle;


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

class TextureAllocator {


    private:
        friend class Texture;
        std::map<TextureHandle,Texture> m_textures;
        TextureHandle m_nextHandle;
    public:

        template <size_t N = 1>
        TextureHandle CreateTexture(LocalTextureSpecs<N> specs);
        TextureHandle CreateTexture(VirtualTextureSpecs specs);
        TextureHandle CreateTexture(RuntimeTextureSpecs specs);

};


#include "TextureAllocator.inl"
#pragma once
#include <glad/glad.h>
#include <map>
#include "Texture.h"


typedef unsigned int TextureHandle;

struct TextureSpecs {

    unsigned int wrapping = GL_CLAMP_TO_EDGE;
    unsigned int filtering = GL_LINEAR;
    
    unsigned int format = GL_RGBA;
    unsigned int internal_format = GL_RGBA;
    unsigned int encoding = GL_FLOAT;
    unsigned int type = GL_TEXTURE_2D;
    unsigned int mipmap_levels = 1;


    int target_framebuffer = -1;
};

template <size_t N = 1>
struct LocalTextureSpecs : TextureSpecs {
   
    std::array<std::string, N> path = {"resources/textures/default-abledo.png"};

};

struct RuntimeTextureSpecs : public TextureSpecs {
    int width = -1;
    int height = -1;
    int depth = 1;
};

struct VirtualTextureSpecs : public TextureSpecs {
    int width = -1;
    int height = -1;
    int depth = 1;    

    unsigned int handle = 0;
};

class TextureAllocator {


    private:
        friend class Texture;
        std::map<TextureHandle,Texture> m_textures;

        std::map<unsigned int, TextureHandle> m_framebufferTarget;
        TextureHandle m_nextHandle;


        //To be used to assign an already created texture to the allocator, currently supported 
        TextureHandle createTexture(VirtualTextureSpecs specs);
        
    public:
        inline TextureAllocator() {}

        template <size_t N = 1>
        TextureHandle createTexture(LocalTextureSpecs<N> specs);
        TextureHandle createTexture(RuntimeTextureSpecs specs);


        inline Texture& getTexture(TextureHandle handle) { return m_textures[handle]; }

        void releaseTexture(TextureHandle handle);

        void updateResolutionFBTextures(unsigned int framebuffer, int x, int y);
};


#include "TextureAllocator.inl"
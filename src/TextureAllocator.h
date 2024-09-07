#pragma once
#include <glad/glad.h>
#include <map>
#include "Texture.h"
#include <vector>


typedef unsigned int TextureHandle;




class TextureAllocator {

    public:
        struct TextureSpecification;
        struct RuntimeTextureSpecification;
        struct VirtualTextureSpecification;
        struct LocalTextureSpecification;


    private:
        friend class Texture;
        std::map<TextureHandle,Texture> m_textures;

        std::map<unsigned int, std::vector<TextureHandle>> m_framebufferTarget;
        TextureHandle m_nextHandle;


        //To be used to assign an already created texture to the allocator, currently supported 
        TextureHandle createTexture(VirtualTextureSpecification& specs);
        
    public:
        inline TextureAllocator() {}

        TextureHandle createTexture(LocalTextureSpecification& specs);
        TextureHandle createTexture(RuntimeTextureSpecification& specs);


        inline Texture& getTexture(TextureHandle handle) { return m_textures[handle]; }

        void releaseTexture(TextureHandle handle);

        void updateResolution(unsigned int resolutionGroup, int x, int y);
};


struct TextureAllocator::TextureSpecification {

    unsigned int wrapping = GL_CLAMP_TO_EDGE;
    unsigned int filtering = GL_LINEAR;
    
    unsigned int format = GL_RGBA;
    unsigned int internal_format = GL_RGBA;
    unsigned int encoding = GL_FLOAT;
    unsigned int type = GL_TEXTURE_2D;
    unsigned int mipmap_levels = 1;


    int target_framebuffer = -1;

    TextureHandle override = 0;
};

struct TextureAllocator::RuntimeTextureSpecification  : public TextureAllocator::TextureSpecification {
    int width;
    int height;
    int depth;
    unsigned int resolution_group = 0;
};

struct  TextureAllocator::VirtualTextureSpecification : public TextureAllocator::TextureSpecification {

    unsigned int id = 0;
    unsigned int handle = 0;

};

struct TextureAllocator::LocalTextureSpecification : public TextureAllocator::TextureSpecification {
    std::vector<std::string> texture_paths;
};

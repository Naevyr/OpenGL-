#include "Texture.h"
#include <glad/glad.h>
#include <array>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>



#include "Program.h"



Texture Texture::CreateTexture(RuntimeTextureSpecs specs) {
    Texture texture;
    texture.m_textureType = specs.type;

    glGenTextures(1, &texture.m_textureID);
    glBindTexture(specs.type, texture.m_textureID);

    texture.m_width = specs.width;
    texture.m_height = specs.height;

    
    texture.m_format = specs.format;
    texture.m_internalFormat = specs.internal_format;
    
    
    
    if(specs.depth > 1)
        glTexImage3D(specs.type, 0, specs.internal_format, specs.width, specs.height, specs.depth, 0, specs.format, specs.encoding, nullptr);

    else
        glTexImage2D(specs.type, 0, specs.internal_format, specs.width, specs.height, 0, specs.format, specs.encoding, nullptr);

    
    glTexParameteri(specs.type, GL_TEXTURE_WRAP_S, specs.wrapping);
    glTexParameteri(specs.type, GL_TEXTURE_WRAP_T, specs.wrapping);
    if(specs.type == GL_TEXTURE_CUBE_MAP)
        glTexParameteri(specs.type, GL_TEXTURE_WRAP_T, specs.wrapping);



    glTexParameteri(specs.type, GL_TEXTURE_MIN_FILTER, specs.mipmap_levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : specs.filtering );
    glTexParameteri(specs.type, GL_TEXTURE_MAG_FILTER, specs.filtering);


    if(specs.mipmap_levels > 1)
        glGenerateMipmap(specs.type);
    return texture;
}

Texture Texture::CreateTexture(VirtualTextureSpecs specs) {

    Texture texture;

    texture.m_textureID = specs.handle;
    
    texture.m_textureType = specs.type;
    
    texture.m_width = specs.width;
    texture.m_height = specs.height;

    texture.m_format = specs.internal_format;

    return texture;
}

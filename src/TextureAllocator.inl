#pragma once

#include <stb/stb_image.h>

class Texture;


template <size_t N>
TextureHandle TextureAllocator::createTexture(LocalTextureSpecs<N> specs)
{


    stbi_set_flip_vertically_on_load(1);

    int width, height, channels;
 
    unsigned char * m_data = stbi_load(specs.path[0].c_str(), &width, &height, &channels, 0);


    RuntimeTextureSpecs runtime_spec;
    runtime_spec.width = width;
    runtime_spec.height = height;
    runtime_spec.format = specs.format;
    runtime_spec.depth = specs.type == GL_TEXTURE_CUBE_MAP ? 1 : N;


    TextureHandle handle = TextureAllocator::createTexture(runtime_spec);

    Texture& texture = m_textures[handle];


    glBindTexture(specs.type,texture.GetTextureID());

    if(N > 1)
    {
        stbi_image_free(m_data);
        for(int i = 0; i < N; i++)
        {   
            int width, height, channels;
            unsigned char * m_data = stbi_load(specs.path[i].c_str(), &width, &height, &channels, 0);
            if(specs.type == GL_TEXTURE_CUBE_MAP)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, specs.internal_format,  width, height, 0,specs.format, specs.encoding, m_data);
            else
                glTexSubImage3D(specs.type, 0, 0, 0, 0, texture.m_width, texture.m_height,i , specs.format, specs.encoding, m_data);


            stbi_image_free(m_data);
        }
    }
    else
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture.m_width, texture.m_height, specs.format, specs.encoding, m_data);
        stbi_image_free(m_data);
    }




    return handle;
}

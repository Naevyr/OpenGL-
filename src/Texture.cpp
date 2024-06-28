#include "Texture.h"
#include <glad/glad.h>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "Program.h"

Texture Texture::LoadTexture(std::string file_path)
{


    stbi_set_flip_vertically_on_load(1);


    int width, height, channels;
    unsigned char * m_data = stbi_load(file_path.c_str(), &width, &height, &channels, 0);
    Texture texture = Texture::CreateTexture(width, height, channels);



    GLint format = texture.m_channels == 3 ? GL_RGB : GL_RGBA;
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture.m_width, texture.m_height, format, GL_UNSIGNED_BYTE, m_data);
    
    stbi_image_free(m_data);
    return texture;
}

Texture Texture::LoadTextureArray(std::string file_paths[], int count)
{
    stbi_set_flip_vertically_on_load(1);


    int width, height, channels;

    unsigned char * m_data = stbi_load(file_paths[0].c_str(), &width, &height, &channels, 0);
    Texture texture = Texture::AllocateTextureArray(width, height, channels, count);
    
    GLint format = texture.m_channels == 3 ? GL_RGB : GL_RGBA;
    for(int i = 0; i < count; i++)
    {    
        unsigned char * m_data = stbi_load(file_paths[0].c_str(), &width, &height, &channels, 0);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, texture.m_width, texture.m_height,i , format, GL_FLOAT, m_data);
        stbi_image_free(m_data);
    }

    return texture;

}


Texture Texture::CreateTexture(int width, int height, int channels) {
    Texture texture;
    texture.m_textureType = GL_TEXTURE_2D;

    glGenTextures(1, &texture.m_textureID);
    glBindTexture(GL_TEXTURE_2D, texture.m_textureID);

    texture.m_width = width;
    texture.m_height = height;
    texture.m_channels = channels;
    
    
    GLint format = texture.m_channels == 3 ? GL_RGB : GL_RGBA;


    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

Texture Texture::CreateTexture(unsigned int openglHandle, unsigned int type) {

    Texture texture;

    texture.m_textureID = openglHandle;
    texture.m_virtualHandle = true;
    texture.m_textureType = type;

    return texture;
}

Texture Texture::AllocateTextureArray(int width, int height, int channels, int count) {

    Texture texture;
    texture.m_textureType = GL_TEXTURE_2D_ARRAY;


    glGenTextures(1, &texture.m_textureID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture.m_textureID);

    texture.m_width = width;
    texture.m_height = height;
    texture.m_channels = channels;
    
    
    GLint format = texture.m_channels == 3 ? GL_RGB : GL_RGBA;


    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, count, 0, format, GL_UNSIGNED_BYTE, nullptr);
    
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}


Texture Texture::LoadCubeMap(std::array<std::string,6> file_paths){

    Texture texture;
    texture.m_textureType = GL_TEXTURE_CUBE_MAP;
    
    texture.m_channels = 4;

    glGenTextures(1, &texture.m_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.m_textureID);



    for(int i = 0; i < 6; i++)
    {

        int width, height, channels;

        unsigned char * m_data = stbi_load(file_paths[i].c_str(), &width, &height, &channels, 0);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

        stbi_image_free(m_data);



        assert(texture.m_width == width  || (i == 0));
        assert(texture.m_height == height || (i == 0));


        texture.m_width = width;
        texture.m_height = height;


    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

void Texture::Bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(m_textureType, m_textureID);
}



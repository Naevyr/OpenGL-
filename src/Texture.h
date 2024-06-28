#pragma once
#include <string>
#include <array>
class Texture {
    private:
        unsigned int m_textureID;
        unsigned int m_textureType;


        int m_width;
        int m_height;
        int m_channels;


        bool m_virtualHandle = false;

        
    public:

        inline Texture() {}
        
        static Texture LoadTexture(std::string path = "");
        static Texture LoadTextureArray(std::string file_paths[], int count);
        static Texture CreateTexture(unsigned int openglHandle, unsigned int type);
        static Texture CreateTexture(int width, int height, int channels);
        static Texture AllocateTextureArray(int width, int height, int channels, int count);
        static Texture LoadCubeMap(std::array<std::string,6> file_paths);



        void Bind(unsigned int unit) const;
        inline int GetWidth() const  { return m_width; }
        inline int GetHeight() const { return m_height; }    

};


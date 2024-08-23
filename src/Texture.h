#pragma once
#include <string>
#include <array>



class Texture {
    private:
        unsigned int m_textureID;
        unsigned int m_textureBindlessHandle;


        unsigned int m_textureType;
        
        unsigned int m_format;
        unsigned int m_internalFormat;


        int m_width;
        int m_height;


        
    public:
        friend class TextureAllocator;

        inline Texture() {}
        
       


        inline unsigned int GetTextureID() const { return m_textureID; }
        inline unsigned int GetTextureHandle() const { return m_textureBindlessHandle; }

        inline int GetWidth() const  { return m_width; }
        inline int GetHeight() const { return m_height; } 
        inline unsigned int GetFormat() const {return m_format; }   
        inline unsigned int GetInternalFormat() const {return m_internalFormat; }   

        inline unsigned int GetTextureType() const { return m_textureType; }


        

};


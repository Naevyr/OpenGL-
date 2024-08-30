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
        
       


       
        inline unsigned int getHandle() const { return m_textureBindlessHandle; }
        inline unsigned int getID() const { return m_textureID; }
        inline int getWidth() const  { return m_width; }
        inline int getHeight() const { return m_height; } 
        inline unsigned int getFormat() const {return m_format; }   
        inline unsigned int getInternalFormat() const {return m_internalFormat; }   

        inline unsigned int getType() const { return m_textureType; }




        

};


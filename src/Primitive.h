#pragma once
#include "VertexArray.h"

class Primitive {
    private:
        VertexArray m_vertexArray;
        unsigned int m_materialIndex;
        
    public:
        Primitive(VertexArray vertexArray, unsigned int materialIndex);
    

        inline unsigned int getMaterialIndex() { return m_materialIndex; }
};
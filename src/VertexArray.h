#pragma once
#include "VertexBuffer.h"
class VertexArray {
    private:
        unsigned int m_arrayID;
        VertexBuffer m_vertexBuffer;
    public:
        inline VertexArray() {}
        VertexArray(unsigned char * data, unsigned int size);

        void Release();
        void Bind() const;
};
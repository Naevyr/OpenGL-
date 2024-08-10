#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory>


class VertexArray {
    private:
        unsigned int m_arrayID;

        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        IndexBuffer m_indexBuffer;
    public:

        inline VertexArray() {}
        VertexArray(std::vector<unsigned char> vertices, std::vector<unsigned int> indices, std::shared_ptr<VertexBuffer> vertexBuffer);

        void Release();
        void Bind() const;
};
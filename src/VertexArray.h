#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>




class VertexArray {

    public:

        enum Type{
            STATIC_MESH
        };


        struct StaticMeshLayout {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texcoord;
        };
        struct Specifications {
            Type type;
            std::vector<unsigned char> vertices;
            std::vector<unsigned int> indices;
            std::shared_ptr<VertexBuffer> vertexBuffer;
        };

  


    private:

        unsigned int m_arrayID;
        unsigned int m_meshID;


        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        IndexBuffer m_indexBuffer;

        void StaticMeshDefinition();

    public:

        inline VertexArray() {};
        VertexArray(Specifications specs);
        void Bind() const;
        void Release();
        
};


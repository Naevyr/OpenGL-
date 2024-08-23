#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Node.h"
#include <memory>
#include <glm/gtc/quaternion.hpp>


class Mesh : public Node
{
    public: 
    
        enum Type{
            STATIC,
            DYNAMIC
        };

    private:

        Type m_meshType;

    public:

        inline Type getMeshType() { return m_meshType; }
        static void LoadFromFile(std::string path, Type type, std::vector<unsigned char>& vertices, std::vector<unsigned int>& indices);
        
};

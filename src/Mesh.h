#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include <memory>
#include <glm/gtc/quaternion.hpp>


class Mesh
{
    private:
        unsigned int m_meshID;
        VertexArray m_vertexArray;
        IndexBuffer m_indexBuffer;

        unsigned int m_materialIndex;

        glm::vec3 m_position = glm::vec3(0, 0, 0);
        glm::vec3 m_scale = glm::vec3(1, 1, 1);
        glm::quat m_orientation = glm::quat(0, 0, 0, 1);
        
    public:
        Mesh(const char * filename, unsigned int materialIndex);
        
        
        void Draw(Material& material);

        inline glm::vec3 getPosition() { return m_position; }
        inline glm::vec3 getScale() { return m_scale; }
        inline glm::quat getOrientation() { return m_orientation; }

        inline void setPosition(glm::vec3 position) { m_position = position; }
        inline void setScale(glm::vec3 scale) { m_scale = scale; }
        inline void setOrientation(glm::quat orientation) { m_orientation = orientation; }

        inline unsigned int getMaterialIndex() { return m_materialIndex; }

        
};

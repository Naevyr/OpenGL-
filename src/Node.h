#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <optional>


typedef unsigned int NodeID; 

class Node {
    
    private:
        NodeID m_nodeID = 0;

        NodeID m_parent = 0;
        std::vector<NodeID> m_children;

    protected:
        glm::vec3 m_position;
        glm::vec3 m_scale;
        glm::quat m_orientation;

    
    public: 
        Node() {}
    
        inline glm::vec3 getPosition() { return m_position; }
        inline glm::vec3 getScale() { return m_scale; }
        inline glm::quat getOrientation() { return m_orientation; }

        inline void setPosition(glm::vec3 position) { m_position = position; }
        inline void setScale(glm::vec3 scale) { m_scale = scale; }
        inline void setOrientation(glm::quat orientation) { m_orientation = orientation; }



        inline void addChild(NodeID child) { m_children.push_back(child); }
        inline void setParent(NodeID parent ) { m_parent = m_nodeID;  }
        inline void removeAt(int index) { m_children.erase(m_children.begin() + index); }

};
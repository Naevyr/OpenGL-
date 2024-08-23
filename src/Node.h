#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <optional>


class Node {
    
    private:
        
        std::vector<std::shared_ptr<Node>> m_children;
        std::optional<std::shared_ptr<Node>> m_parent;
    

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

        inline void addChild(std::unique_ptr<Node> child) { m_children.push_back(std::move(child)); }
        inline void setParent(std::unique_ptr<Node> parent) { m_parent = std::move(parent); }
        inline void removeAt(int index) { m_children.erase(m_children.begin() + index); }


        inline std::vector<std::unique_ptr<Node>>& getChildren() { return m_children; }
        inline std::optional<std::unique_ptr<Node>>& getParent() { return m_parent; }
};
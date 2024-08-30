#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <span>


#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Node.h"
#include "scene/SceneDescription.h"
#include "scene/EnvironmentDescription.h"

struct PrimitiveGroup {
    std::span<Primitive&> primitives;
    std::optional<PrimitiveGroup> next_pass;
};




class Scene 
{
    private:

        std::vector<NodeID> m_primitives;
        std::vector<NodeID> m_lights;

        std::map<NodeID, Node> m_nodes;
        

        NodeID m_rootNode;
        NodeID m_Camera;


        EnvironmentDescription m_Environment;


    public:
        inline Scene() {}



        inline void setEnvironment(EnvironmentDescription environment) { m_Environment = environment; }
        inline EnvironmentDescription& getEnvironment() { return m_Environment; }

        PrimitiveGroup getPrimitiveGroup();

        inline Camera& getCamera() { return std::dynamic_cast<Camera&>(&m_nodes[m_Camera]); } 

        static Scene Load(SceneDescription description);

};  
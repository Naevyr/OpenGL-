#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <span>


#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Node.h"
#include "TextureAllocator.h"
#include "scene/SceneDescription.h"
#include "scene/EnvironmentDescription.h"

struct PrimitiveGroup {
    std::span<Primitive> primitives;
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
        Scene(SceneDescription description, std::shared_ptr<TextureAllocator> textureAllocator);



        inline void setEnvironment(EnvironmentDescription environment) { m_Environment = environment; }
        inline EnvironmentDescription& getEnvironment() { return m_Environment; }
        inline Camera& getCamera() { return (Camera&)m_nodes[m_Camera]; } 

        std::vector<std::reference_wrapper<Light>> getLights();
        std::vector<std::reference_wrapper<Mesh>> getMeshes();

        
        PrimitiveGroup getPrimitiveGroup();



};  
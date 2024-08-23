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

        std::vector<Primitive&> m_primitives;
        Camera m_Camera;
        EnvironmentDescription m_Environment;
        Node m_rootNode;


    public:
        inline Scene() {}



        inline void SetEnvironment(EnvironmentDescription environment) { m_Environment = environment; }
        inline EnvironmentDescription& GetEnvironment() { return m_Environment; }

        PrimitiveGroup GetPrimitiveGroup();

        inline Camera& GetCamera() { return m_Camera; }

        static Scene Load(SceneDescription description);

};  
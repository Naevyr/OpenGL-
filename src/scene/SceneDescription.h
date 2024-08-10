#pragma once 
#include "Camera.h"
#include "LightDescription.h"
#include "MeshDescription.h"
#include "Environment.h"


class SceneDescription
{


    private:
            Camera m_Camera;
            std::vector<MeshDescription> m_Meshes;
            std::vector<LightDescription> m_Lights;
            Environment m_Environment;
    
    public:
        inline SceneDescription() {}
        inline void AddMesh(MeshDescription mesh) { m_Meshes.push_back(mesh); }
        inline std::vector<MeshDescription>& GetMeshes() { return m_Meshes; };
        
        inline void AddLight(LightDescription light) { m_Lights.push_back(light); }
        inline std::vector<LightDescription>& GetLights() { return m_Lights; }
        inline void SetEnvironment(Environment environment) { m_Environment = environment; }
        inline Environment& GetEnvironment() { return m_Environment; }

        

        inline Camera& GetCamera() { return m_Camera; }
};

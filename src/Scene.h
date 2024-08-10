#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"
#include "Environment.h"
class Scene 
{
    private:
        Camera m_Camera;


        
        std::vector<Mesh> m_Meshes;
        std::vector<Light> m_Lights;
        Environment m_Environment;
    
    public:
        inline Scene() {}

        
        inline void AddMesh(Mesh mesh) { m_Meshes.push_back(mesh); }
        inline std::vector<Mesh>& GetMeshes() { return m_Meshes; };
        
        inline void AddLight(Light light) { m_Lights.push_back(light); }
        inline std::vector<Light>& GetLights() { return m_Lights; }
        inline void SetEnvironment(Environment environment) { m_Environment = environment; }
        inline Environment& GetEnvironment() { return m_Environment; }

        

        inline Camera& GetCamera() { return m_Camera; }
};  
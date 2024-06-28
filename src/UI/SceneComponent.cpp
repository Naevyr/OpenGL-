#include "SceneComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "CollapsedEntityComponent.h"
#include <imgui/imgui.h>
std::set<int> SceneComponent::m_displayedLights;
std::set<int> SceneComponent::m_displayedMeshes;


void SceneComponent::Render(Scene& scene) {


    std::vector<Light>& lights = scene.GetLights();
    std::vector<Mesh>& meshes =  scene.GetMeshes();

    glm::vec3 camPos = scene.GetCamera().getPosition();
    ImGui::DragFloat3("Camera Position",&camPos[0]);
    scene.GetCamera().setPosition(camPos);
    
    
    
    

    ImGui::BeginChild("Entities", ImVec2(0,0), true);

    for(int i = 0; i < lights.size(); i++)
    {
        bool expand;
        CollapsedEntityComponent::Render("Light " + i, expand);
        if(expand)
            m_displayedLights.insert(i);

        if(m_displayedLights.count(i) == 0)
            continue;
            
        bool close;
        LightComponent::Render(lights[i], close);
        if(close)
            m_displayedLights.erase(i);
    }



    for(int i = 0; i < meshes.size(); i++)
    {
        bool expand;
        CollapsedEntityComponent::Render("Mesh " + i,expand);
        if(expand)
            m_displayedMeshes.insert(i);

        if(m_displayedMeshes.count(i) == 0)
            continue;
        bool close;
        MeshComponent::Render(meshes[i], close);
        if(close)
            m_displayedMeshes.erase(i); 

    }


    ImGui::EndChild();

    std::set<int> filteredLights;

    for(auto light : m_displayedLights)
    {
        if(light < lights.size())
            filteredLights.insert(light);
    };
    m_displayedLights = filteredLights;



    std::set<int> filteredMeshes;

    for(auto mesh : m_displayedMeshes)
    {
        if(mesh < meshes.size())
            filteredMeshes.insert(mesh);
    };
    m_displayedMeshes = filteredMeshes;

  
    

    ImGui::SeparatorText("Environment");
    ImGui::ColorPicker3("Background", &scene.GetEnvironment().globalIllumination[0]);
    ImGui::DragFloat("Global Illumination Intensity", &scene.GetEnvironment().globalIlluminationIntensity, 0.01f, 0.0f, 1.0f);



    
}
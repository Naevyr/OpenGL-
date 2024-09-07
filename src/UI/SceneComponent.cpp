#include "SceneComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "CollapsedEntityComponent.h"
#include <imgui/imgui.h>
std::set<int> SceneComponent::m_displayedLights;
std::set<int> SceneComponent::m_displayedMeshes;


void SceneComponent::Render(Scene& scene) {


    auto lights = scene.getLights();
    auto meshes =  scene.getMeshes();

    glm::vec3 camPos = scene.getCamera().getPosition();
    ImGui::DragFloat3("Camera Position",&camPos[0]);
    scene.getCamera().setPosition(camPos);
    
    
    
    

    ImGui::BeginChild("Entities", ImVec2(0,0), true);

    for(int i = 0; i < lights.size(); i++)
    {
        bool expand;
        CollapsedEntityComponent::Render("Light " + i, expand);


        if(expand)
            m_displayedLights.insert(i);

        if(m_displayedLights.count(i) == 0)
            continue;
            
        bool keepOpen = true;
        LightComponent::Render(lights[i], &keepOpen);
        if(!keepOpen)
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
        bool keepOpen = true;
        MeshComponent::Render(meshes[i], &keepOpen);
        if(!keepOpen)
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
   
    

    
}
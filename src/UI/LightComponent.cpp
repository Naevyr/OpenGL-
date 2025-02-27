#include "LightComponent.h"
#include <imgui/imgui.h>



void LightComponent::Render(Light& light, bool* keepOpen)
{   
    ImGui::Begin("Light", keepOpen);


    ImGui::DragFloat3("Light Position", &light.position[0]);
    ImGui::DragFloat("Light Intensity", &light.intensity, 0.01f, 0.0f, 10.0f);
    ImGui::ColorPicker3("Light Color", &light.color[0]);

    
    
    ImGui::End();
    
}
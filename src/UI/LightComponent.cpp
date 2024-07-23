#include "LightComponent.h"
#include <imgui/imgui.h>



void LightComponent::Render(Light& light, bool& close)
{   
    ImGui::Begin("Light", &close);


    ImGui::DragFloat3("Light Position", &light.position[0]);
    ImGui::DragFloat("Light Intensity", &light.intensity, 0.01f, 0.0f, 1.0f);
    ImGui::ColorPicker3("Light Color", &light.color[0]);

    
    
    ImGui::End();
    close = !close;
}
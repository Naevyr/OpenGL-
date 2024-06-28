#include "LightComponent.h"
#include <imgui/imgui.h>



void LightComponent::Render(Light& light, bool& close)
{   
    ImGui::Begin("Light", &close);


    ImGui::DragFloat3("Light Position", &light.position[0]);
    ImGui::ColorPicker3("Light Color", &light.color[0]);

    
    
    ImGui::End();
    close = !close;
}
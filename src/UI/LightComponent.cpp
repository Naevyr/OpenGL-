#include "LightComponent.h"

#include <imgui/imgui.h>

void LightComponent::Render(Light& light, bool* keepOpen) {
	ImGui::Begin("Light", keepOpen);

	ImGui::DragFloat3("Light Position", &light.m_position[0]);

	ImGui::DragFloat("Light Intensity", &light.m_intensity, 0.01f, 0.0f, 10.0f);
	ImGui::ColorPicker3("Light Color", &light.m_color[0]);

	ImGui::End();
}
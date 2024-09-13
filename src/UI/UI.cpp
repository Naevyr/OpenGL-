

#include "UI.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include "SceneComponent.h"

void UI::Render(Scene& scene, PostProcessingEffects& effects) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Scene");
	SceneComponent::Render(scene);

	ImGui::BeginChild("Post Processing Effects");
	ImGui::Checkbox("Bloom", &effects.bloom);

	ImGui::EndChild();
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
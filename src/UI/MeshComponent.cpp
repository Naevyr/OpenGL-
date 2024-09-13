#include "MeshComponent.h"

#include <imgui/imgui.h>

void MeshComponent::Render(Mesh& mesh, bool* keepOpen) {
	ImGui::Begin("Mesh", keepOpen);
	glm::vec3 position = mesh.getPosition();
	ImGui::DragFloat3("Mesh Position", &position[0]);

	mesh.setPosition(position);

	glm::quat orientation = mesh.getOrientation();
	ImGui::DragFloat4("Mesh Orientation", &orientation[0]);

	mesh.setOrientation(orientation);

	ImGui::End();
}

#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

Camera::Camera() { m_localPosition = glm::vec3(0.0f, 0.0f, 0.0f); }

void Camera::movementInput(glm::vec3 direction, float delta) {
	glm::vec3 forward = glm::vec4(direction, -1) * getOrientation();
	m_localPosition += forward * delta * (!m_speeding ? 10.0f : 30.0f);
}
void Camera::rotationInput(glm::vec2 rotation, float delta) {
	m_pitch += rotation.y * delta * 100.0f;
	m_yaw += rotation.x * delta * 100.0f;
}

glm::mat4 Camera::getOrientation() const {
	glm::quat q = glm::angleAxis(glm::radians(m_pitch), glm::vec3(1, 0, 0));
	q *= glm::angleAxis(glm::radians(m_yaw), glm::vec3(0, 1, 0));
	return glm::mat4_cast(q);
}
#include "Node.h"

void Node::setPosition(glm::vec3 position) {
	glm::vec3 movementOffset = m_localPosition - position;
	m_localPosition += movementOffset;
	m_globalPosition += movementOffset;

	for (auto child : m_children)
		child.setGlobalPosition(m_globalPosition + child.getPosition());
}

void Node::setScale(glm::vec3 scale) {
	glm::vec3 scaleOffset = m_localScale - scale;
	m_localScale += scaleOffset;
	m_globalScale += scaleOffset;

	for (auto child : m_children)
		child.setGlobalScale(m_globalScale + child.getScale());
}

void Node::setOrientation(glm::quat orientation) {
	glm::quat orientationOffset = m_localOrientation - orientation;
	m_localOrientation += orientationOffset;
	m_globalOrientation += orientationOffset;

	for (auto child : m_children)
		child.setGlobalOrientation(
			m_globalOrientation + child.getOrientation()
		);
}

void Node::setGlobalPosition(glm::vec3 globalPosition) {
	if (m_parent == nullptr) {
		glm::vec3 movementOffset = globalPosition - m_localPosition;
		m_localPosition += movementOffset - m_parent->getGlobalPosition();
		m_globalPosition = globalPosition;

	} else
		m_localPosition = globalPosition;

	for (auto&& child : m_children)
		child.setGlobalPosition(m_globalPosition + child.getPosition());
}

void Node::setGlobalScale(glm::vec3 globalScale) {
	if (m_parent == nullptr) {
		glm::vec3 scaleOffset = globalScale - m_localScale;
		m_localScale += scaleOffset - m_parent->getGlobalScale();
		m_globalScale = globalScale;

	} else
		m_localScale = globalScale;

	for (auto&& child : m_children)
		child.setGlobalScale(m_globalScale + child.getScale());
}

void Node::setGlobalOrientation(glm::quat globalOrientation) {
	if (m_parent == nullptr) {
		glm::quat orientationOffset = globalOrientation - m_localOrientation;
		m_localOrientation +=
			orientationOffset - m_parent->getGlobalOrientation();
		m_globalOrientation = globalOrientation;

	} else
		m_localOrientation = globalOrientation;

	for (auto&& child : m_children)
		child.setGlobalOrientation(
			m_globalOrientation + child.getOrientation()
		);
}
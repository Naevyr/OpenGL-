#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

#include "glm/fwd.hpp"

typedef unsigned int NodeID;

class Node {
private:
	NodeID m_nodeID = 0;

	Node* m_parent = nullptr;
	std::vector<Node> m_children;

protected:
	glm::vec3 m_localPosition = glm::vec3(0);
	glm::vec3 m_localScale = glm::vec3(1);
	glm::quat m_localOrientation = glm::quat();

	glm::vec3 m_globalPosition = glm::vec3(0);
	glm::vec3 m_globalScale = glm::vec3(1);
	glm::quat m_globalOrientation = glm::quat();

public:
	Node(NodeID nodeID, Node* parent) : m_nodeID(nodeID), m_parent(parent) {}

	inline glm::vec3 getPosition() { return m_localPosition; }
	inline glm::vec3 getScale() { return m_localScale; }
	inline glm::quat getOrientation() { return m_localOrientation; }

	inline void setPosition(glm::vec3 position);
	inline void setScale(glm::vec3 scale);
	inline void setOrientation(glm::quat orientation);

	inline glm::vec3 getGlobalPosition() { return m_globalPosition; }
	inline glm::vec3 getGlobalScale() { return m_globalScale; }
	inline glm::quat getGlobalOrientation() { return m_globalOrientation; }

	void setGlobalPosition(glm::vec3 position);
	void setGlobalScale(glm::vec3 scale);
	void setGlobalOrientation(glm::quat orientation);

	inline void addChild(Node child) { m_children.push_back(child); }
	inline void setParent(Node* parent) { m_parent = parent; }
	inline void removeAt(int index) {
		m_children.erase(m_children.begin() + index);
	}

	~Node() {}
};
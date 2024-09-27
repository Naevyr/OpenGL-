#pragma once

#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>

#include "Node.h"
#include "Primitive.h"

class Mesh : public Node {
public:
	AABB m_boundingBox;

	enum Type {
		STATIC,
		DYNAMIC
	};
	std::vector<Primitive> m_primitives;

private:
	Type m_meshType;

public:
	Mesh(std::vector<Primitive> primitives, NodeID id, NodeID parent) :
		Node(id, parent), m_primitives(primitives) {}
	Mesh(std::vector<Primitive> primitives, NodeID id) :
		Node(id), m_primitives(primitives) {}

	Type getMeshType() { return m_meshType; }

	inline void addChild(Primitive primitive) {
		m_primitives.push_back(primitive);
	}

	inline std::vector<Primitive> getPrimitives() const { return m_primitives; }

	static void LoadFromFile(
		std::string path,
		Type type,
		std::vector<unsigned char>& vertices,
		std::vector<unsigned int>& indices
	);
};

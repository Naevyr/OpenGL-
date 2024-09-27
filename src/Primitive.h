#pragma once
#include "AABB.h"
#include "Node.h"
#include "ResourceTypes.h"
#include "VertexArray.h"

class Primitive : public Node {
public:
	struct ViewProjectionUniformBuffer {
		glm::mat4 u_view;
		glm::mat4 u_projection;
	};

private:
	VertexArray m_vertexArray;
	MaterialHandle m_material;

public:
	Primitive(
		VertexArray vertexArray,
		MaterialHandle materialHandle,
		NodeID id,
		NodeID parent
	) :
		Node(id, parent),
		m_vertexArray(vertexArray),
		m_material(materialHandle) {}
	inline MaterialHandle getMaterialIndex() { return m_material; }
	inline VertexArray getVertexArray() { return m_vertexArray; }
};
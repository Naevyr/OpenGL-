#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <span>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class VertexArray {
public:
	enum Type {
		STATIC_MESH
	};

	struct StaticMeshLayout {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};
	struct Specifications {
		Type type;
		std::span<unsigned char> vertices;
		std::span<unsigned char> indices;
		std::shared_ptr<VertexBuffer> vertexBuffer;
	};

private:
	GLuint m_arrayID;
	unsigned int m_meshID;

	std::shared_ptr<VertexBuffer> m_vertexBuffer;
	IndexBuffer m_indexBuffer;

	void StaticMeshDefinition();

public:
	VertexArray(Specifications& specs);
	inline unsigned int getIndexCount() { return m_indexBuffer.getCount(); }
	void bind() const;
	void release();
};

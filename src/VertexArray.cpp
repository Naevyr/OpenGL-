#include "VertexArray.h"

#include <glad/glad.h>

#include <cstdint>
#include <glm/glm.hpp>

VertexArray::VertexArray(Specifications specs) :
	m_vertexBuffer(specs.vertexBuffer) {
	m_indexBuffer = IndexBuffer(specs.indices);
	m_meshID = m_vertexBuffer->addMesh(specs.vertices);

	switch (specs.type) {
		case Type::STATIC_MESH:
			StaticMeshDefinition();
			break;
	}
}
void VertexArray::Release() {
	glDeleteVertexArrays(1, &m_arrayID);
	m_vertexBuffer->removeMesh(m_meshID);
}

void VertexArray::Bind() const { glBindVertexArray(m_arrayID); }

void VertexArray::StaticMeshDefinition() {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(uintptr_t)(3 * sizeof(float))
	);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(uintptr_t)(6 * sizeof(float))
	);
};
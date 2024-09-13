#include "IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(std::vector<unsigned int> data) :
	m_count(data.size() / sizeof(unsigned int)) {
	glGenBuffers(1, &m_glID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glID);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		data.size() * sizeof(unsigned int),
		data.data(),
		GL_STATIC_DRAW
	);
}

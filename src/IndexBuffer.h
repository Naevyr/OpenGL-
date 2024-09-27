#pragma once

#include <span>

#include "glad/glad.h"


class IndexBuffer {
private:
	GLuint m_glID;
	unsigned int m_count;

public:
	inline IndexBuffer() {}
	IndexBuffer(std::span<unsigned char> data);
	void bind();
	inline unsigned int getCount() const { return m_count; }
};
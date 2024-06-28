#include "VertexBuffer.h"
#include <glad/glad.h>
VertexBuffer::VertexBuffer(void * data, unsigned int size) {

    glGenBuffers(1, &m_glID);
    glBindBuffer(GL_ARRAY_BUFFER, m_glID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_glID);
}
void update(float* data, int size)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

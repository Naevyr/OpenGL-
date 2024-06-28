#include "VertexArray.h"
#include <glad/glad.h>
#include <cstdint>

VertexArray::VertexArray(unsigned char * data, unsigned int count) {

    glGenVertexArrays(1, &m_arrayID);
    glBindVertexArray(m_arrayID);

    
    m_vertexBuffer = VertexBuffer(data, count);
    m_vertexBuffer.bind();


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),  (void*)(uintptr_t)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(uintptr_t)(6 * sizeof(float)));

}
void VertexArray::Release()
{
    glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::Bind() const
{
    m_vertexBuffer.bind();
    glBindVertexArray(m_arrayID);
}
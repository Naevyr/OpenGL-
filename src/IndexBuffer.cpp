#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(void * data, unsigned int count) : m_count(count){

    glGenBuffers(1, &m_glID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    
} 

void IndexBuffer::Release(){
    glDeleteBuffers(1, &m_glID);
}
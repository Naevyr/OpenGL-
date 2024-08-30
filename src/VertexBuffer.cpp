#include "VertexBuffer.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cstring>




VertexBuffer::VertexBuffer() {

    glGenBuffers(1, &m_glID);
    glBindBuffer(GL_ARRAY_BUFFER, m_glID);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
}




void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_glID);
}


unsigned int VertexBuffer::addMesh(std::vector<unsigned char>& data)
{

    assert(!m_isStatic);

    glBufferSubData(GL_ARRAY_BUFFER, m_offsets[0].size, data.size(), data.data());

    m_instancedMeshes++;
    unsigned int meshID = m_instancedMeshes;

    DataOffset offset;
    offset.offset = m_offsets[0].size;
    offset.size = data.size();

    m_offsets[meshID] = offset;

    m_offsets[0].size += data.size();


    return meshID;

};

void VertexBuffer::removeMesh(unsigned int m_meshID){

    assert(!m_isStatic);




    unsigned char* ptr = (unsigned char*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    assert(ptr);


    std::vector<unsigned char> buffer(
        ptr,
        ptr + m_offsets[0].size
    );

    buffer.erase(
        buffer.begin() + m_offsets[m_meshID].offset,
        buffer.begin() + m_offsets[m_meshID].offset + m_offsets[m_meshID].size
    );


    glBufferData(GL_ARRAY_BUFFER, m_offsets[0].size - m_offsets[m_meshID].size, nullptr, GL_DYNAMIC_DRAW);
    unsigned int oldBuffer = m_glID;
    glBindBuffer(GL_ARRAY_BUFFER, m_glID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_offsets[0].size - m_offsets[m_meshID].size, ptr);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glDeleteBuffers(1, &oldBuffer);



    auto size =  m_offsets[0].size;

    auto lowerBound =  m_offsets.lower_bound(m_meshID);
    lowerBound ++;
    for (auto it = lowerBound; it != m_offsets.end(); it++) {
        it->second.offset -= size;
    }
    

    m_offsets.erase(m_meshID);
};
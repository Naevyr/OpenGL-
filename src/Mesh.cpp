#include "Mesh.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader/tiny_obj_loader.h"
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

Mesh::Mesh(const char * filename, unsigned int materialIndex) : m_materialIndex(materialIndex) {
   

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool loadout = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename);


    if(!loadout) {
        std::cout << "Failed to load .obj file" << std::endl;
        return;
    }





    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++) {
        size_t fv = size_t(shapes[0].mesh.num_face_vertices[f]);

        for (size_t v = 0; v < fv; v++) {
            tinyobj::index_t idx = shapes[0].mesh.indices[index_offset + v];
            
            
            
            tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
            tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
            tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

            tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
            tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
            tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
        

            tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
            tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];


    
            vertices.push_back(Vertex{
                glm::vec3(vx, vy, vz),
                glm::vec3(nx, ny, nz),
                glm::vec2(tx, ty)
            });
            indices.push_back(index_offset);
        }
        index_offset += fv;
    }
    m_vertexArray = VertexArray((unsigned char*) &vertices[0], vertices.size() * (sizeof(float) * 8));
    m_indexBuffer = IndexBuffer((unsigned char*) &indices, indices.size());
};



void Mesh::Draw(Material &material){

    
    m_vertexArray.Bind();
    material.SetUniform<glm::mat4>(
        "u_Model",
        glm::scale(glm::translate(glm::mat4(1), getPosition()) *  glm::mat4_cast(getOrientation()), getScale()) 
    );

    glDrawArrays(GL_TRIANGLES, 0, m_indexBuffer.getCount());

}

#include <glm/mat4x4.hpp>

#include "Material.h"


Material::Material(const char * vertexPath, const char * fragmentPath) {
    m_programID = Program::Create(vertexPath, fragmentPath);
}

void Material::Use() {
    Bind();


    int i = 0;
    for(auto texture : m_textures)
    {
        (texture.second).get().Bind(i);
        SetUniform<int>(texture.first,i);
        i++;
    }
        
}

void Material::Bind() {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    if(currentProgram != m_programID)
        glUseProgram(m_programID);
}
void SetTextureUniform(Texture& texture,unsigned int unit) {


}





void Material::BindBlock(std::string name, unsigned int id) {



    glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, name.c_str()), id);
}


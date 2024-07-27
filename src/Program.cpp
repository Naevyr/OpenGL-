#include "Program.h"
#include <glad/glad.h>

void Program::Initialize() {

    m_programID = glCreateProgram();

}


Program::~Program(){

    //glDeleteProgram(m_programID);
}



void Program::Bind() {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    if(currentProgram != m_programID)
        glUseProgram(m_programID);
}


void Program::BindBlock(std::string name, unsigned int id) {
    Bind();
    glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, name.c_str()), id);
}


template<>
void Program::SetUniform(std::string name, glm::mat4 value) {
    Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);

}


template<>
void Program::SetUniform(std::string name, glm::vec4 value) {
Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform4fv(location, 1, &value[0]);

}
template<>
void Program::SetUniform(std::string name, glm::vec3 value) {
Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform3fv(location, 1, &value[0]);

}


template<>
void Program::SetUniform(std::string name, glm::vec2 value) {
Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform2fv(location, 1, &value[0]);


}

template<>
void Program::SetUniform(std::string name, float value) {
Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(location, value );
}

template<>
void Program::SetUniform(std::string name, int value) {
    Bind();
    unsigned int location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1i(location, value );
}


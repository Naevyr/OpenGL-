
#include <glm/mat4x4.hpp>

#include "Material.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


Material::Material(std::string vertexPath, std::string fragmentPath) {
    
    Program::Initialize();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    
    }

    catch (std::ifstream::failure e) {

        std::cout << "Error Shaders not loaded correctly" << std::endl;
        throw;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();



    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);


    int success;
    char log[512];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      
        glGetShaderInfoLog(vertex, 512, NULL, log);
        std::cout << log << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);



    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
      

        glGetShaderInfoLog(vertex, 512, NULL, log);
          std::cout << log << std::endl;
    }


    glAttachShader(m_programID, vertex);
    glAttachShader(m_programID, fragment);

    glLinkProgram(m_programID);
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);
        for (char i: infoLog)
            std::cout << i;
        throw "Material did not compile";
    }
 

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Material::Use() {
    Program::Bind();


    int i = 0;
    for(auto texture : m_textures)
    {
        (texture.second).get().Use(i);
        SetUniform<int>(texture.first,i);
        i++;
    }
        
}

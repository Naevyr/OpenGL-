#include "ComputeShader.h"



#include <glad/glad.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

ComputeShader::ComputeShader(std::string path) {
    
    Program::Initialize();

    
    unsigned int shader;
    std::string source;
    std::ifstream file;

    try
    {
        file.open(path);
        
        std::stringstream shaderStream;
        shaderStream << file.rdbuf();
        
        file.close();
        source = shaderStream.str();

    }

    catch (std::ifstream::failure e) {

        std::cout << "Error Compute Shader not loaded correctly" << std::endl;
        throw;
    }

    const char * cSource = source.c_str(); 

    shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader,1,&cSource,NULL);
    glCompileShader(shader);
    
    int success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cout << log << std::endl;
    }


    glAttachShader(m_programID,shader);
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
        throw "Compute shader link failed";
    }
}

void ComputeShader::Dispatch(glm::ivec3 groupCount) {
    Bind();
    glDispatchCompute(groupCount.x, groupCount.y, groupCount.z);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ComputeShader::SetTexture(unsigned int unit, Texture& texture)
{
    ComputeShader::SetTexture(unit, texture, 0, GL_READ_WRITE);
}
void ComputeShader::SetTexture(unsigned int unit, Texture& texture, int mipmap, unsigned int usage, std::string samplerName) {
    
    Bind();

    if(samplerName == "")
    {
        glBindImageTexture(unit, texture.GetTextureID(), mipmap, GL_FALSE, 0, usage, texture.GetInternalFormat());
        return;
    }   
    

    glActiveTexture(GL_TEXTURE0 + unit); 
    
    glBindTexture(texture.GetTextureType(), texture.GetTextureID());

    GLint inputTexLocation = glGetUniformLocation(m_programID, samplerName.c_str());
    glUniform1i(inputTexLocation, unit);  

    SetUniform<int>("mipmapLevel", mipmap);
}
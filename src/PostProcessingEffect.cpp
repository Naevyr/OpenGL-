#include "PostProcessingEffect.h"

#include <glad/glad.h>
#include <string>


PostProcessingEffect<ComputeShader>::PostProcessingEffect(std::string computeShaderPath) {
    m_program = ComputeShader(computeShaderPath);
}

void PostProcessingEffect<ComputeShader>::Run(Texture& input, Texture& output) {
    m_program.Bind();
    glBindImageTexture(0, input.GetTextureID(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);

    glBindImageTexture(1, output.GetTextureID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    
    m_program.Dispatch({output.GetWidth(), output.GetHeight(), 1});
}
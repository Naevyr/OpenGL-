#include "ComputeShader.h"
#include "Material.h"

#include "Texture.h"
#include "TextureAllocator.h"



template <>
inline SinglePassPostProcessingEffect<ComputeShader>::SinglePassPostProcessingEffect(std::string computeShaderPath) {
    m_program = ComputeShader(computeShaderPath);
}

template <>
inline void SinglePassPostProcessingEffect<ComputeShader>::run(Texture& input, Texture& output) {
    m_program.Bind();
    

    
    m_program.SetTexture("u_input",input,0,GL_READ_ONLY);
    m_program.SetTexture("u_output",output,0,GL_WRITE_ONLY);

    m_program.Dispatch({output.getWidth(), output.getWidth(), 1});
    
}



#include "SinglePassPostProcessingEffect.h"
#include "ComputeShader.h"
#include "Material.h"

template <class>
class SinglePassPostProcessingEffect;

#pragma region Compute
template<>
class SinglePassPostProcessingEffect<ComputeShader> : public PostProcessingEffect {

    private: 
        ComputeShader m_program;

    public:

        void Initialize() override;
        void Initialize(std::string shaderPath);
        void Run(Texture& input, Texture& output);
};



void SinglePassPostProcessingEffect<ComputeShader>::Initialize(std::string computeShaderPath) {
    m_program = ComputeShader(computeShaderPath);
}

void SinglePassPostProcessingEffect<ComputeShader>::Run(Texture& input, Texture& output) {
    m_program.Bind();
    
    m_program.SetTexture(0,input,0,GL_READ_ONLY);
    m_program.SetTexture(1,input,0,GL_WRITE_ONLY);

    m_program.Dispatch({output.GetWidth(), output.GetHeight(), 1});
}

#pragma endregion Compute

#pragma region Material
template<>
class SinglePassPostProcessingEffect<Material> {

    
    public:
        
        void Initialize(std::string fragmentShaderPath);
        void Run(Texture& input, Texture& output);
        
};
#pragma endregion Material

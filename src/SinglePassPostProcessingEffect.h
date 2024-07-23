#pragma once
#include "ComputeShader.h"
#include "Material.h"


template <typename T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

   
    public:
        
        virtual void Initialize(std::string shaderPath);
        virtual void Run(Texture& input, Texture& output);
};



template<>
class SinglePassPostProcessingEffect<ComputeShader> {

    private: 
        ComputeShader m_program;

    public:
        SinglePassPostProcessingEffect() {}
        SinglePassPostProcessingEffect(std::string computeShaderPath);
        virtual void Run(Texture& input, Texture& output);
};

template<>
class SinglePassPostProcessingEffect<Material> {

    
    public:
        
        virtual void Initialize(std::string fragmentShaderPath);
        virtual void Run(Texture& input, Texture& output);
        
};



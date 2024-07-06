#pragma once
#include "ComputeShader.h"
#include "Material.h"


template <typename T>
class PostProcessingEffect {

   
    public:
        
        virtual void Initialize(std::string shaderPath);
        virtual void Run(Texture& input, Texture& output);
};

template<>
class PostProcessingEffect<ComputeShader> {

    private: 
        ComputeShader m_program;

    public:
        PostProcessingEffect() {}
        PostProcessingEffect(std::string fragmentShaderPath);
        virtual void Run(Texture& input, Texture& output);
};

template<>
class PostProcessingEffect<Material> {

    
    public:
        
        virtual void Initialize(std::string computeShaderPath);
        virtual void Run(Texture& input, Texture& output);
        
};



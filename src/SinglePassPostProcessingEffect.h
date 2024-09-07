#pragma once

#include "PostProcessingEffect.h"
#include "TextureAllocator.h"


template <class T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

    protected: 
        T m_program;

    public:
        inline SinglePassPostProcessingEffect(){}
        SinglePassPostProcessingEffect(std::string shaderPath, TextureAllocator& textureAllocator);
        
        
        void Run(TextureHandle input, TextureHandle output);
};



#include "SinglePassPostProcessingEffect.inl"


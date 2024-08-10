#pragma once

#include "PostProcessingEffect.h"


template <class T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

    protected: 
        T m_program;

    public:
        inline SinglePassPostProcessingEffect(){}
        SinglePassPostProcessingEffect(std::string shaderPath);
        
        
        void Run(Texture& input, Texture& output);
};



#include "SinglePassPostProcessingEffect.inl"


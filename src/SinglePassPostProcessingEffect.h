#pragma once

#include "PostProcessingEffect.h"


template <class T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

    protected: 
        T m_program;

    public:
        inline void Initialize() override { throw "Please use the correct overload."; } 
        void Initialize(std::string shaderPath);
        void Run(Texture& input, Texture& output);
};



#include "SinglePassPostProcessingEffect.inl"


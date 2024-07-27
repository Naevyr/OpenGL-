#pragma once

#include "PostProcessingEffect.h"
// #include "SinglePassPostProcessingEffect.inl"

template <typename T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

   
    public:
        inline void Initialize() override { throw "Please use the correct overload."; } 
        virtual Initialize(std::string shaderPath);
        virtual void Run(Texture& input, Texture& output);
};






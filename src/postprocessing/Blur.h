#pragma once
#include "SinglePassPostProcessingEffect.h"
#include "ComputeShader.h"

class Blur : public SinglePassPostProcessingEffect<ComputeShader> {
    
    private:
        int m_blurSize;
    public:

        inline void Initialize() override { SinglePassPostProcessingEffect<ComputeShader>::Initialize("resources/shaders/compute/blur.glsl"); } 
        void Run(Texture& input, Texture& output, int blurSize = 3);

};
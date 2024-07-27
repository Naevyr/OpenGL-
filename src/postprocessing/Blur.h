#pragma once
#include "SinglePassPostProcessingEffect.h"
#include "ComputeShader.h"

class Blur : SinglePassPostProcessingEffect<ComputeShader> {
    public:

        inline void Initialize() override { SinglePassPostProcessingEffect<ComputeShader>::Initialize("resources/shaders/compute/blur.glsl"); } 
};
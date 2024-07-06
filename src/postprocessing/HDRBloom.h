#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"

class HDRBloom : public PostProcessingEffect<ComputeShader> {

    public: 
        inline HDRBloom() {}
        inline HDRBloom(std::string computeShaderPath) : PostProcessingEffect<ComputeShader>(computeShaderPath) {}
        void Run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
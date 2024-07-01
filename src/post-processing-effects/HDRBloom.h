#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"

class HDRBloom : public PostProcessingEffect<ComputeShader> {

    public: 
        void Run(Texture& input, Texture& output) override;
};
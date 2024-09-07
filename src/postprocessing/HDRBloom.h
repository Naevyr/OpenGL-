#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"
#include "SinglePassPostProcessingEffect.h"
#include "TextureAllocator.h"

class HDRBloom : public PostProcessingEffect {
    private:
        SinglePassPostProcessingEffect<ComputeShader> m_brightPass;
        


        ComputeShader m_blur;
        ComputeShader m_downSample;
        ComputeShader m_upSample;
        ComputeShader m_add;

        TextureHandle m_workTexture;
        TextureHandle m_temporary;
        TextureAllocator*  m_textureAllocator;

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        HDRBloom(TextureAllocator& textureAllocator);
        
        
        void Run(TextureHandle input, TextureHandle output) override;
        inline ~HDRBloom() {} 
};
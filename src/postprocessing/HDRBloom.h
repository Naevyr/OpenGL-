#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"
#include "SinglePassPostProcessingEffect.h"
#include "Texture.h"
#include "TextureAllocator.h"
#include <memory>

class HDRBloom : public PostProcessingEffect {
    private:
        SinglePassPostProcessingEffect<ComputeShader> m_brightPass;
        


        ComputeShader m_blur;
        ComputeShader m_downSample;
        ComputeShader m_upSample;
        ComputeShader m_add;

        TextureHandle m_workTexture;
        TextureHandle m_temporary;
        std::shared_ptr<TextureAllocator>  m_textureAllocator;

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        HDRBloom(std::shared_ptr<TextureAllocator> textureAllocator);
        
        
        void run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
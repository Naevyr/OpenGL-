#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"
#include "SinglePassPostProcessingEffect.h"
#include <string>
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
        

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        HDRBloom(std::shared_ptr<TextureAllocator> textureAllocator);

        
        void Run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"
#include "SinglePassPostProcessingEffect.h"
#include <string>
class HDRBloom : public PostProcessingEffect {
    private:
        SinglePassPostProcessingEffect<ComputeShader> m_brightPass;


        
        ComputeShader m_downSample;
        ComputeShader m_upSample;


        Texture m_brightPassOutput;
        Texture m_upsampledOutput;
        

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        
        void Initialize() override;
        void Run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
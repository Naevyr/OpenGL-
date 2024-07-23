#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"

class HDRBloom : public PostProcessingEffect {
    private:
        ComputeShader m_brightPass;
        ComputeShader m_downSample;
        ComputeShader m_upSample;


        Texture m_brightPassOutput;
        Texture m_upsampledOutput;
        

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        HDRBloom(std::string computeShaderPath);
        void Run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
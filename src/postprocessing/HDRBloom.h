#pragma once

#include "PostProcessingEffect.h"
#include "ComputeShader.h"
#include "SinglePassPostProcessingEffect.h"
#include <string>
class HDRBloom : public PostProcessingEffect {
    private:
        SinglePassPostProcessingEffect<ComputeShader> m_brightPass;
        


        ComputeShader m_blur;
        ComputeShader m_downSample;
        ComputeShader m_upSample;
        ComputeShader m_add;

        Texture m_workTexture;
        Texture m_temporary;
        

        float m_bloomThreshold;

    public: 
        inline HDRBloom() {}
        
        void Initialize() override;
        void Run(Texture& input, Texture& output) override;
        inline ~HDRBloom() {} 
};
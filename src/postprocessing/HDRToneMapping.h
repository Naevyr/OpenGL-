#pragma once

#include "SinglePassPostProcessingEffect.h"
#include "Material.h"

class HDRToneMapping :  public SinglePassPostProcessingEffect<Material> {
    private: 
        

    public: 

        HDRToneMapping() {}
        HDRToneMapping(std::string shaderPath);

        void Run(Texture& input, Texture& output) override;
};
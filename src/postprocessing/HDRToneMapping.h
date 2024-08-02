#pragma once

#include "SinglePassPostProcessingEffect.h"
#include "Material.h"

class HDRToneMapping :  public SinglePassPostProcessingEffect<Material> {
    private: 
        

    public: 

    
        void Initialize(std::string shaderPath) override;
        void Run(Texture& input, Texture& output) override;

        HDRToneMapping() {}

};
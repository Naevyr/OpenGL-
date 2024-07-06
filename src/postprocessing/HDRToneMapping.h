#pragma once

#include "PostProcessingEffect.h"
#include "Material.h"

class HDRToneMapping :  public PostProcessingEffect<Material> {
    private: 
        

    public: 
        void Run(Texture& input, Texture& output) override;
        HDRToneMapping() {}

};
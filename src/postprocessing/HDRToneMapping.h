#pragma once

#include "SinglePassPostProcessingEffect.h"
#include "Material.h"
#include "TextureAllocator.h"

class HDRToneMapping :  public SinglePassPostProcessingEffect<Material> {
    private: 
        

    public: 

        HDRToneMapping() {}
        HDRToneMapping(std::string shaderPath);

        void run(Texture& input, Texture& output) override;
};
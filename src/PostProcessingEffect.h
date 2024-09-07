#pragma once

#include "TextureAllocator.h"

class PostProcessingEffect {

    protected:
        PostProcessingEffect();

    public:
        virtual void Run(TextureHandle input, TextureHandle output) = 0;

};


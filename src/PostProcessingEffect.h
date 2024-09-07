#pragma once

#include "Texture.h"
#include "TextureAllocator.h"

class PostProcessingEffect {

    protected:
        PostProcessingEffect();

    public:
        virtual void run(Texture& input, Texture& output) = 0;

};


#pragma once
#include <string>
#include "Texture.h"

class PostProcessingEffect {

    protected:
        PostProcessingEffect();

    public:
        virtual void Run(Texture& input, Texture& output) = 0;

};


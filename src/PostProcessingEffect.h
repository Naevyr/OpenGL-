#pragma once
#include <string>
#include "Texture.h"

class PostProcessingEffect {

   
    public:
        virtual void Initialize() = 0;
        virtual void Run(Texture& input, Texture& output) = 0;

};


#pragma once

#include "PostProcessingEffect.h"
#include "Texture.h"
#include "TextureAllocator.h"
#include <memory>


template <class T>
class SinglePassPostProcessingEffect : public PostProcessingEffect {

    protected: 
        T m_program;
       

        
    public:
        inline SinglePassPostProcessingEffect(){}
        SinglePassPostProcessingEffect(std::string shaderPath);
        
        
        void run(Texture& input, Texture& output);
};



#include "SinglePassPostProcessingEffect.inl"


#pragma once
#include "SinglePassPostProcessingEffect.h"
#include "ComputeShader.h"

class Blur : public SinglePassPostProcessingEffect<ComputeShader> {
    
    private:
        int m_blurSize;
    public:
        inline Blur() {}
        Blur(int blurSize);
        void run(Texture& input, Texture& output) override;

};
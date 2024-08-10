#include "Blur.h"
void Blur::Blur(int blurSize) {
    m_blurSize = blurSize;
    SinglePassPostProcessingEffect<ComputeShader>::SinglePassPostProcessingEffect<ComputeShader>("resources/shaders/compute/blur.glsl");
}

void Blur::Run(Texture& input, Texture& output) {
    m_program.SetUniform("u_blurSize", m_blurSize);
    SinglePassPostProcessingEffect<ComputeShader>::Run(input, output);
}
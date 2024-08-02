#include "Blur.h"
void Blur::Run(Texture& input, Texture& output, int blurSize) {
    m_program.SetUniform("u_blurSize", m_blurSize);
    SinglePassPostProcessingEffect<ComputeShader>::Run(input, output);
}
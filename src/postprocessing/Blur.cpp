#include "Blur.h"
Blur::Blur(int blurSize) :
	SinglePassEffect<ComputeShader>("resources/shaders/compute/blur.glsl") {
	m_blurSize = blurSize;
}

void Blur::run(Texture& input, Texture& output) {
	m_program->setUniform("u_blurSize", m_blurSize);
	SinglePassEffect<ComputeShader>::run(input, output);
}
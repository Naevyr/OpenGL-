#include "Blur.h"
Blur::Blur(int blurSize) {
	m_blurSize = blurSize;
	SinglePassPostProcessingEffect<ComputeShader>(
		"resources/shaders/compute/blur.glsl"
	);
}

void Blur::run(Texture& input, Texture& output) {
	m_program.SetUniform("u_blurSize", m_blurSize);
	SinglePassPostProcessingEffect<ComputeShader>::run(input, output);
}
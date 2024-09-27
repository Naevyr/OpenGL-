#pragma once
#include "ComputeShader.h"
#include "SinglePassComputeEffect.h"
#include "SinglePassPostProcessingEffect.h"

class Blur : public SinglePassComputeEffect {
private:
	int m_blurSize;

public:
	Blur(int blurSize);

	void run(Texture& input, Texture& output) override;
};
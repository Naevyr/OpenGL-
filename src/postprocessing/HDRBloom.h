#pragma once

#include <memory>

#include "ComputeShader.h"
#include "PostProcessingEffect.h"
#include "SinglePassPostProcessingEffect.h"
#include "Texture.h"
#include "TextureManager.h"

class HDRBloom : public PostProcessingEffect {
private:
	SinglePassPostProcessingEffect<ComputeShader> m_brightPass;

	ComputeShader m_blur;
	ComputeShader m_downSample;
	ComputeShader m_upSample;
	ComputeShader m_add;

	TextureHandle m_workTexture;
	TextureHandle m_temporary;
	std::shared_ptr<TextureManager> m_TextureManager;

	float m_bloomThreshold;

public:
	inline HDRBloom() {}
	HDRBloom(std::shared_ptr<TextureManager> TextureManager);

	void run(Texture& input, Texture& output) override;
	inline ~HDRBloom() {}
};
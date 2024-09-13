#pragma once
#include <memory>
#include <vector>

#include "Light.h"
#include "Material.h"
#include "TextureManager.h"
#include "pipeline/Pipeline.h"
#include "scene/EnvironmentDescription.h"

class ForwardPipeline : public Pipeline {
private:
	unsigned int m_ColorFB;

	unsigned int m_LightUBO;

	TextureHandle m_shadowMap;

	Material m_shadowMaterial;

	std::vector<Material> m_materials;

	std::shared_ptr<TextureManager> m_TextureManager;

	void setLightUniform(
		std::vector<Light>& lights, EnvironmentDescription& environment
	);
	void setTransformUniform(glm::mat4 projection, glm::mat4 view);

public:
	inline ForwardPipeline() {}

	ForwardPipeline(std::shared_ptr<TextureManager> TextureManager);

	void render(RenderSpecifications& specs) override;
	void setup(Renderer::RenderFeatures renderFeatures) override;

	inline ~ForwardPipeline() {}
};

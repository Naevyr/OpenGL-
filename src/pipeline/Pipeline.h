#pragma once

#include <glm/glm.hpp>

#include "RenderPass.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "Scene.h"

class Pipeline {
public:
	struct RenderSpecifications;

private:
	struct LightUBO;

	unsigned int m_ShadowFB;
	TextureHandle m_shadowMap;
	MaterialHandle m_shadowMapMaterial;

	std::shared_ptr<ResourceManager> m_resourceManager;

	void renderShadowMap(Scene& scene);

public:
	Pipeline(std::shared_ptr<ResourceManager> resourceManager);

	void render(RenderSpecifications& specs);
	void renderSubpass(RenderPassSpecs& renderPassSpecs);
};

struct Pipeline::RenderSpecifications {
	Scene& scene;

	TextureHandle colorTexture;
	TextureHandle depthTexture;
};

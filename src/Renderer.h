#pragma once

#include <memory>
#include <optional>

#include "Material.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "postprocessing/HDRBloom.h"
#include "scene/SceneDescription.h"

class Pipeline;

class Renderer {
public:
	enum class RenderFeatures;

private:
	std::unique_ptr<Pipeline> m_pipeline;
	std::shared_ptr<ResourceManager> m_resourceManager;

	std::optional<Scene> m_currentScene;

	TextureHandle m_framebufferColor;
	TextureHandle m_framebufferDepth;
	TextureHandle m_temporaryBuffer;

	std::unique_ptr<HDRBloom> m_bloom;

	glm::mat4 m_projection, m_view;

	int m_width, m_height;

	unsigned int m_mainPassFBO;

	static unsigned int s_quadVAO;
	static Program s_quadMaterial;

public:
	Renderer(int width, int height);

	Scene& loadScene(SceneDescription& scene);

	void setResolution(int width, int height);
	void render();

	static void DrawQuad(Texture& texture);
};

enum class Renderer::RenderFeatures {
	LIGHTING = 1 << 0,
	SHADOWS = 1 << 1,
	SKYBOX = 1 << 2,
	BLOOM = 1 << 3,
};
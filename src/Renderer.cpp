
#include "Renderer.h"

#include <memory>

#include "Program.h"
#include "ResourceManager.h"
#include "TextureManager.h"
#include "pipeline/Pipeline.h"
#include "postprocessing/HDRBloom.h"
#include "scene/SceneDescription.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

Renderer::Renderer(int width, int height) {
	setResolution(width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	m_resourceManager = std::make_shared<ResourceManager>();

	m_pipeline = std::make_unique<Pipeline>(m_resourceManager);

	m_bloom = std::make_unique<HDRBloom>(m_resourceManager);

	TextureManager::RuntimeTextureSpecification framebufferSpecs;
	framebufferSpecs.width = width;
	framebufferSpecs.height = height;
	framebufferSpecs.internal_format = GL_RGBA32F;
	framebufferSpecs.encoding = GL_FLOAT;
	framebufferSpecs.resolution_group = 0;

	TextureManager& textureManager = m_resourceManager->getTextureManager();
	m_framebufferColor = textureManager.createTexture(framebufferSpecs);
	m_temporaryBuffer = textureManager.createTexture(framebufferSpecs);

	TextureManager::RuntimeTextureSpecification depth_specs;

	depth_specs.type = GL_TEXTURE_2D;
	depth_specs.width = width;
	depth_specs.height = height;
	depth_specs.filtering = GL_NEAREST;
	depth_specs.format = GL_DEPTH_COMPONENT;
	depth_specs.internal_format = GL_DEPTH_COMPONENT;
	depth_specs.resolution_group = 0;

	m_framebufferDepth = textureManager.createTexture(depth_specs);

	glGenFramebuffers(1, &m_mainPassFBO);
}

Scene& Renderer::loadScene(SceneDescription& description) {
	m_currentScene = Scene(description, m_resourceManager);
	return m_currentScene.value();
};

void Renderer::render() {
	TextureManager& textureManager = m_resourceManager->getTextureManager();
	Texture& fbColor = textureManager.getTexture(m_framebufferColor);
	Texture& fbDepth = textureManager.getTexture(m_framebufferDepth);
	Texture& tmp = textureManager.getTexture(m_temporaryBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_mainPassFBO);
	glFramebufferTexture(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbColor.getID(), 0
	);
	glFramebufferTexture(
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbDepth.getID(), 0
	);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_view = m_currentScene.value().getCamera().getOrientation() *
	         glm::translate(
				 glm::mat4(1), m_currentScene.value().getCamera().getPosition()
			 );

	Pipeline::RenderSpecifications specs = {
		.scene = m_currentScene.value(),
		.colorTexture = m_framebufferColor,
		.depthTexture = m_framebufferDepth,
	};

	m_pipeline->render(specs);

	glBindFramebuffer(GL_FRAMEBUFFER, m_mainPassFBO);
	glBindTexture(GL_TEXTURE_2D, fbColor.getID());
	glFramebufferTexture(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbColor.getID(), 0
	);
	glFramebufferTexture(
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbDepth.getID(), 0
	);

	Renderer::DrawQuad(
		m_resourceManager->getTextureManager().getTexture(m_framebufferColor)
	);
}

void Renderer::setResolution(int width, int height) {
	m_width = width;
	m_height = height;
	m_projection = glm::perspective(
		glm::radians(45.0f), (float)width / height, 0.1f, 1000.0f
	);

	m_resourceManager->getTextureManager().updateResolution(0, width, height);
}

void Renderer::DrawQuad(Texture& texture) {
	if (s_quadVAO == 0) {
		s_quadMaterial = Program(
			"resources/shaders/quad.vert", "resources/shaders/quad.frag"
		);
		glGenVertexArrays(1, &s_quadVAO);
	}

	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(s_quadVAO);
	s_quadMaterial.setUniform("u_Texture", texture);
	s_quadMaterial.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

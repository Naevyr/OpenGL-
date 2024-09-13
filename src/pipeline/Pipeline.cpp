
#include "pipeline/Pipeline.h"

#include <functional>

#include "Material.h"
#include "Pipeline.h"
#include "ResourceTypes.h"
#include "glad/glad.h"
#include "scene/MaterialDescription.h"

Pipeline::Pipeline(std::shared_ptr<ResourceManager> resourceManager) :
	m_resourceManager(resourceManager) {
	TextureManager::RuntimeTextureSpecification shadowMapSpecs;
	shadowMapSpecs.width = 256;
	shadowMapSpecs.height = 256;
	shadowMapSpecs.format = GL_DEPTH_COMPONENT;
	shadowMapSpecs.internal_format = GL_DEPTH_COMPONENT24;
	shadowMapSpecs.encoding = GL_FLOAT;
	shadowMapSpecs.type = GL_TEXTURE_2D_ARRAY;
	shadowMapSpecs.depth = 20;
	m_shadowMap =
		m_resourceManager->getTextureManager().createTexture(shadowMapSpecs);

	Light::Uniform lightUniform;
	UBOHandle uboHandle = m_resourceManager->registerUBO(lightUniform);
	Material shadowmapMaterial =
		Material::ShadowmapMaterial(uboHandle, m_shadowMap);

	m_shadowMapMaterial =
		m_resourceManager->registerMaterial(shadowmapMaterial);
}

void Pipeline::renderShadowMap(Scene& scene) {
	Texture& shadowmap =
		m_resourceManager->getTextureManager().getTexture(m_shadowMap);

	std::vector<std::reference_wrapper<Light>> lights = scene.getLights();

	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFB);

	glBindTexture(GL_TEXTURE_3D, shadowmap.getID());
	glTexImage3D(
		GL_TEXTURE_2D_ARRAY,
		0,
		GL_DEPTH_COMPONENT24,
		256,
		256,
		lights.size(),
		0,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		nullptr
	);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 256, 256);

	for (size_t i = 0; i < lights.size(); i++) {
		glFramebufferTextureLayer(
			GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowmap.getID(), 0, i
		);
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 lightProjectionMatrix;

		switch (lights[i].get().getType()) {
			case Light::Type::DIRECTIONAL:
				lightProjectionMatrix =
					glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 100.0f);
				break;
			case Light::Type::SPOT:
				lightProjectionMatrix =
					glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

				break;
			case Light::Type::POINT:
				throw std::runtime_error("Point light not supported");
			default:
				break;
		};
		glm::mat4 lightViewMatrix = glm::lookAt(
			lights[i].position,
			lights[i].position + direction,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		lightViewMatrix[1][1] *= -1;

		glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

		scene.GetLights()[i].lightSpaceMatrix = lightSpaceMatrix;
		m_shadowMaterial.Bind();
		m_shadowMaterial.SetUniform<glm::mat4>(
			"u_LightSpace", lightSpaceMatrix
		);

		for (auto mesh : scene.GetMeshes()) {
			mesh.Draw(m_shadowMaterial);
		}
	}
};

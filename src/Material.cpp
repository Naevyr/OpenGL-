#include "Material.h"

#include "Program.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "TextureManager.h"

void Material::bindUniforms(ResourceManager& resourceManager) {
	TextureManager& textureManager = resourceManager.getTextureManager();
	Program& program = resourceManager.getProgram(m_program);
	program.bind();

	for (auto [name, uniform] : m_uniformsDataValues) {
		std::visit(
			[name, &program](auto& uniformValue) {
				program.setUniform(name, uniformValue);
			},
			uniform
		);
	}

	for (auto [name, uniform] : m_uniformHandleValues) {
		std::visit(
			[name, resourceManager, textureManager, &program](auto& uniformValue
		    ) {
				if constexpr (std::is_same_v<
								  decltype(uniformValue),
								  TextureHandle>) {
					program.setUniform(
						name, textureManager.getTexture(uniformValue)
					);
				} else if constexpr (std::is_same_v<
										 decltype(uniformValue),
										 UBOHandle>) {
					program.setUBO(name, resourceManager.getUBO(uniformValue));
				}
			},
			uniform
		);
	}
}

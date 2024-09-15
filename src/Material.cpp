#include "Material.h"

#include "Program.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "TextureManager.h"

void Material::bindUniforms(
	Program& program, ResourceManager& resourceManager
) {
	TextureManager& textureManager = resourceManager.getTextureManager();

	for (auto uniform : m_uniforms) {
		std::visit(
			[program, uniform, resourceManager, textureManager](
				auto& uniformValue
			) {
				if constexpr (std::is_same_v<
								  decltype(uniformValue),
								  TextureHandle>) {
					program.setUniform(
						uniform.first, textureManager.getTexture(uniformValue)
					);
				} else if constexpr (std::is_same_v<
										 decltype(uniformValue),
										 UBOHandle>) {
					program.setUBO(
						uniform.first, resourceManager.getUBO(uniformValue)
					);
				} else {
					program.setUniform(uniform.first, uniformValue);
				}
			},
			uniform.second
		);
	}
}

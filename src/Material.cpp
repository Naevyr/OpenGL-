#include "Material.h"

#include "Program.h"
#include "TextureManager.h"

void Material::bindUniforms(Program& program, TextureManager& TextureManager) {
	for (auto texture : textures)
		program.setUniform(
			texture.first, TextureManager.getTexture(texture.second)
		);

	for (auto ubo : ubos) program.setUBO(ubo.first, ubo.second);
}

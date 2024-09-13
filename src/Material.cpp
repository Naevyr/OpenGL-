#include "Material.h"

#include "Program.h"
#include "TextureManager.h"

void StandardMaterial::bindUniforms(
	Program& program, TextureManager& TextureManager
) {
	program.setUniform("u_albedo", TextureManager.getTexture(albedo));
	program.setUniform("u_normal", TextureManager.getTexture(normal));
	program.setUniform("u_roughness", TextureManager.getTexture(roughness));
	program.setUniform("u_specular", TextureManager.getTexture(specular));
	program.setUniform("u_metallic", TextureManager.getTexture(metallic));
	program.setUniform("u_emission", TextureManager.getTexture(emission));
	program.setUniform(
		"u_displacement", TextureManager.getTexture(displacement)
	);

	program.setUBO("u_MVP", meshTransformation);
}

void ShadowMapMaterial::bindUniforms(
	Program& program, TextureManager& TextureManager
) {
	program.setUBO("u_MVP", lightTransformation);
}
#pragma once

#include <glad/glad.h>

#include "Program.h"
#include "ResourceTypes.h"
#include "TextureManager.h"

class Material {
public:
	static Material StandardMaterial(
		ProgramHandle program,

		TextureHandle albedo,
		TextureHandle normal,
		TextureHandle roughness,
		TextureHandle specular,
		TextureHandle metallic,
		TextureHandle emission,
		TextureHandle displacement,
		TextureHandle opacity,

		UBOHandle meshTransformation,
		UBOHandle lightingData
	);

	static Material ShadowmapMaterial(
		ProgramHandle program,
		UBOHandle lightTransformation,
		TextureHandle shadowMap
	);

private:
	Material();

public:
	ProgramHandle program;
	std::map<std::string, TextureHandle> textures;
	std::map<std::string, UBOHandle> ubos;

	virtual void bindUniforms(Program& program, TextureManager& allocator);
};

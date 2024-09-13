#pragma once

#include <glad/glad.h>

#include "Program.h"
#include "TextureManager.h"

struct Material {
	ProgramHandle program;

	virtual void bindUniforms(Program& program, TextureManager& allocator) = 0;
};

struct StandardMaterial : public Material {
	TextureHandle albedo;
	TextureHandle normal;
	TextureHandle roughness;
	TextureHandle specular;
	TextureHandle metallic;
	TextureHandle emission;
	TextureHandle displacement;
	TextureHandle opacity;

	UBOHandle meshTransformation;
	UBOHandle lightingData;

	void bindUniforms(Program& program, TextureManager& allocator) override;
};

struct ShadowMapMaterial : public Material {
	UBOHandle lightTransformation;
	void bindUniforms(Program& program, TextureManager& allocator) override;
};
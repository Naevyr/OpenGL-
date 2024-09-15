#pragma once

#include <glad/glad.h>

#include <variant>

#include "Program.h"
#include "ResourceTypes.h"
#include "TextureManager.h"
#include "glm/ext/matrix_float3x3.hpp"

class ResourceManager;
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

	using UniformValue = std::variant<
		float,
		int,
		TextureHandle,
		UBOHandle,
		glm::vec2,
		glm::vec3,
		glm::vec4,
		glm::mat3,
		glm::mat4>;

	enum class Type {
		FLOAT,
		INT,
		VEC2,
		VEC3,
		VEC4,
		MAT3,
		MAT4
	};

	std::map<std::string, UniformValue> m_uniforms;

public:
	ProgramHandle program;

	void bindUniforms(Program& program, ResourceManager& allocator);

	template <typename T>
	void setUniform(std::string name, T uniform);

	template <typename T>
	std::optional<T> getUniform(std::string name);
};

#pragma once

#include <glad/glad.h>

#include <map>
#include <string>
#include <variant>

#include "ResourceTypes.h"
#include "glm/ext/matrix_float3x3.hpp"

template <typename T>
concept UniformHandleValueType =
	std::same_as<T, TextureHandle> || std::same_as<T, UBOHandle>;

template <typename T>
concept UniformDataValueType =
	std::same_as<T, float> || std::same_as<T, int> ||
	std::same_as<T, glm::vec2> || std::same_as<T, glm::vec3> ||
	std::same_as<T, glm::vec4> || std::same_as<T, glm::mat3> ||
	std::same_as<T, glm::mat4>;

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
		UBOHandle projectionView
	);

	static Material ShadowmapMaterial(
		ProgramHandle program, TextureHandle shadowMap
	);

private:
	Material();

	using UniformHandleValue = std::variant<TextureHandle, UBOHandle>;

	using UniformDataValue = std::variant<
		float,
		int,
		glm::vec2,
		glm::vec3,
		glm::vec4,
		glm::mat3,
		glm::mat4>;

	std::map<std::string, UniformHandleValue> m_uniformHandleValues;
	std::map<std::string, UniformDataValue> m_uniformsDataValues;
	ProgramHandle m_program;

public:
	void bindUniforms(ResourceManager& allocator);

	template <UniformDataValueType T>
	void setUniform(std::string name, T uniform) {
		m_uniformsDataValues[name] = UniformDataValue(uniform);
	}
	template <UniformHandleValueType T>
	void setUniform(std::string name, T value) {
		m_uniformHandleValues[name] = UniformHandleValue(value);
	}

	template <UniformDataValueType T>
	T getUniform(std::string name) {
		return m_uniformsDataValues[name];
	}
	template <UniformHandleValueType T>
	T getUniform(std::string name) {
		return m_uniformHandleValues[name];
	}
};

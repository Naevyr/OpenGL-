#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <string>

#include "Program.h"

class ComputeShader : public Program {
public:
	inline ComputeShader(std::filesystem::path path) : Program(path) {}
	void dispatch(glm::ivec3 axis);

	using Program::setUniform;
	void setUniform(
		std::string name,
		Texture& texture,
		GLenum usage,
		unsigned int mipmap = 0
	);
	inline void setUniform(std::string name, Texture& texture) {
		setUniform(name, texture, GL_READ_ONLY, 0);
	}
};
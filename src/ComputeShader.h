#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <string>

#include "Program.h"

class ComputeShader : public Program {
public:
	ComputeShader(std::string path);
	void Dispatch(glm::ivec3 axis);

	void SetTexture(
		std::string name,
		Texture& texture,
		unsigned int usage,
		unsigned int mipmap = 0
	);
};
#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include <string>

#include "Texture.h"
#include "glm/fwd.hpp"

class Program {
public:
	class STANDARD {
	public:
		inline static const std::filesystem::path VERTEX =
			"resources/shaders/standard.vert";

		inline static const std::filesystem::path FRAGMENT =
			"resources/shaders/fragment.vert";
	};

protected:
	unsigned int m_programID;

public:
	Program(std::filesystem::path vertex, std::filesystem::path fragment);
	Program(std::filesystem::path compute);
	~Program();

	void bind() const;

	void setUniform(std::string name, glm::mat4 value) const;
	void setUniform(std::string name, glm::vec4 value);
	void setUniform(std::string name, glm::vec3 value);
	void setUniform(std::string name, glm::vec2 value);
	void setUniform(std::string name, float value);
	void setUniform(std::string name, int value);
	void setUniform(std::string name, Texture& value);

	void setUBO(std::string name, unsigned int UBO);
};
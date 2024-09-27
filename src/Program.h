#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include <string>

#include "Texture.h"
#include "glm/fwd.hpp"

class Program {
public:
	class DefaultPrograms;

protected:
	GLuint m_programID;

public:
	Program(std::filesystem::path vertex, std::filesystem::path fragment);
	Program(std::filesystem::path compute);
	~Program();

	void bind() const;

	void setUniform(std::string name, glm::mat4 value);
	void setUniform(std::string name, glm::mat3 value);

	void setUniform(std::string name, glm::vec4 value);
	void setUniform(std::string name, glm::vec3 value);
	void setUniform(std::string name, glm::vec2 value);
	void setUniform(std::string name, float value);
	void setUniform(std::string name, int value);
	void setUniform(std::string name, Texture& value);

	void setUBO(std::string name, unsigned int UBO);
};

class Program::DefaultPrograms {
public:
	class STANDARD_FORWARD {
	public:
		inline static const std::filesystem::path VERTEX =
			"resources/shaders/standard.vert";

		inline static const std::filesystem::path FRAGMENT =
			"resources/shaders/fragment.vert";
	};
	class SHADOWMAP {
	public:
		inline static const std::filesystem::path VERTEX =
			"resources/shaders/shadow.vert";

		inline static const std::filesystem::path FRAGMENT =
			"resources/shaders/shadow.vert";
	};
	class SKYBOX {
	public:
		inline static const std::filesystem::path VERTEX =
			"resources/shaders/skybox.vert";

		inline static const std::filesystem::path FRAGMENT =
			"resources/shaders/skybox.vert";
	};
	class QUAD {
	public:
		inline static const std::filesystem::path VERTEX =
			"resources/shaders/quad.vert";

		inline static const std::filesystem::path FRAGMENT =
			"resources/shaders/quad.vert";
	};
};
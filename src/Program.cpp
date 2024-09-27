#include "Program.h"

#include <glad/glad.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

Program::Program(
	std::filesystem::path vertexPath, std::filesystem::path fragmentPath
) {
	m_programID = glCreateProgram();
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	try {
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}

	catch (std::ifstream::failure e) {
		std::cout << "Error Shaders not loaded correctly" << std::endl;
		throw;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	int success;
	char log[512];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << log << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << log << std::endl;
	}

	glAttachShader(m_programID, vertex);
	glAttachShader(m_programID, fragment);

	glLinkProgram(m_programID);
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);
		for (char i : infoLog) std::cout << i;
		throw "Material did not compile";
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Program::Program(std::filesystem::path compute) {
	unsigned int shader;
	m_programID = glCreateProgram();

	std::string source;
	std::ifstream file;

	try {
		file.open(compute);

		std::stringstream shaderStream;
		shaderStream << file.rdbuf();

		file.close();
		source = shaderStream.str();

	}

	catch (std::ifstream::failure e) {
		std::cout << "Error Compute Shader not loaded correctly" << std::endl;
		throw;
	}

	const char* cSource = source.c_str();

	shader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(shader, 1, &cSource, NULL);
	glCompileShader(shader);

	int success;
	char log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << log << std::endl;
	}

	glAttachShader(m_programID, shader);
	glLinkProgram(m_programID);
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);
		for (char i : infoLog) std::cout << i;
		throw "Compute shader link failed";
	}
}

Program::~Program() { glDeleteProgram(m_programID); }

void Program::bind() const {
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	if (currentProgram == m_programID) return;

	glUseProgram(m_programID);
}

void Program::setUBO(std::string name, unsigned int id) {
	bind();
	glUniformBlockBinding(
		m_programID, glGetUniformBlockIndex(m_programID, name.c_str()), id
	);
}

void Program::setUniform(std::string name, glm::mat4 value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
void Program::setUniform(std::string name, glm::mat3 value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}
void Program::setUniform(std::string name, glm::vec4 value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniform4fv(location, 1, &value[0]);
}

void Program::setUniform(std::string name, glm::vec3 value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniform3fv(location, 1, &value[0]);
}

void Program::setUniform(std::string name, glm::vec2 value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniform2fv(location, 1, &value[0]);
}

void Program::setUniform(std::string name, float value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniform1f(location, value);
}

void Program::setUniform(std::string name, int value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniform1i(location, value);
}

void Program::setUniform(std::string name, Texture& value) {
	bind();
	unsigned int location = glGetUniformLocation(m_programID, name.c_str());
	glUniformHandleui64ARB(location, value.getHandle());
}

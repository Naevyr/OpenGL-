#include "ComputeShader.h"

#include <glad/glad.h>

#include <string>

ComputeShader::ComputeShader(std::string path) {}

void ComputeShader::Dispatch(glm::ivec3 groupCount) {
	bind();
	glDispatchCompute(groupCount.x, groupCount.y, groupCount.z);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void SetUniform(
	std::string name,
	Texture& texture,
	unsigned int usage,
	unsigned int mipmap = 0
) {
	GLuint64 imageHandle =
		glGetImageHandleARB(texture.getID(), mipmap, GL_FALSE, 0, usage);
	glMakeImageHandleResidentARB(imageHandle, GL_READ_ONLY);
}
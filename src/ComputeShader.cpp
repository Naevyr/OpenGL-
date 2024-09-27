#include "ComputeShader.h"

#include <glad/glad.h>

#include <string>

#include "Program.h"

void ComputeShader::dispatch(glm::ivec3 groupCount) {
	bind();
	glDispatchCompute(groupCount.x, groupCount.y, groupCount.z);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void setUniform(
	std::string name,
	Texture& texture,
	GLenum usage = GL_READ_WRITE,
	unsigned int mipmap = 0
) {
	GLuint64 imageHandle =
		glGetImageHandleARB(texture.getID(), mipmap, GL_FALSE, 0, usage);
	glMakeImageHandleResidentARB(imageHandle, usage);
}
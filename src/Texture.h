#pragma once

#include "TextureManager.h"
#include "glad/glad.h"

class Texture {
private:
	GLuint m_textureID;
	GLuint m_textureBindlessHandle;

	GLenum m_textureType;

	GLenum m_format;
	GLenum m_internalFormat;

	GLsizei m_width;
	GLsizei m_height;

public:
	friend class TextureManager;

	inline Texture() {}

	inline GLuint getHandle() const { return m_textureBindlessHandle; }
	inline GLuint getID() const { return m_textureID; }
	inline GLsizei getWidth() const { return m_width; }
	inline GLsizei getHeight() const { return m_height; }
	inline GLenum getFormat() const { return m_format; }
	inline GLenum getInternalFormat() const { return m_internalFormat; }

	inline GLenum getType() const { return m_textureType; }
};

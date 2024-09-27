#pragma once
#include <glad/glad.h>

#include <array>
#include <filesystem>
#include <map>
#include <optional>
#include <vector>

#include "ResourceTypes.h"
#include "Texture.h"

class TextureManager {
public:
	struct TextureSpecification;
	struct RuntimeTextureSpecification;
	struct VirtualTextureSpecification;
	template <size_t SIZE = 1>
	struct LocalTextureSpecification;

private:
	friend class Texture;
	TextureHandle m_nextHandle;

	std::map<TextureHandle, Texture> m_textures;

	std::map<unsigned int, std::vector<TextureHandle>> m_resolutionGroups;

	std::map<std::filesystem::path, TextureHandle> m_localTextureCache;

	// To be used to assign an already created texture to the allocator,
	// currently usupported
	TextureHandle createTexture(VirtualTextureSpecification& specs);

public:
	inline TextureManager() {}

	template <size_t SIZE>
	TextureHandle createTexture(LocalTextureSpecification<SIZE>& specs);

	TextureHandle createTexture(RuntimeTextureSpecification& specs);

	inline Texture& getTexture(TextureHandle handle) {
		return m_textures[handle];
	}

	void releaseTexture(TextureHandle handle);

	void updateResolution(unsigned int resolutionGroup, int x, int y);
};

struct TextureManager::TextureSpecification {
	GLint wrapping = GL_CLAMP_TO_EDGE;
	GLint filtering = GL_LINEAR;

	GLenum format = GL_RGBA;
	GLenum internal_format = GL_RGBA;
	GLenum encoding = GL_FLOAT;
	GLenum type = GL_TEXTURE_2D;
	GLint mipmap_levels = 1;

	int target_framebuffer = -1;

	TextureHandle override = 0;
};

struct TextureManager::RuntimeTextureSpecification :
	public TextureManager::TextureSpecification {
	GLsizei height;
	GLsizei width;
	GLsizei depth;
	unsigned int resolution_group = 0;
	std::optional<std::vector<unsigned char>> data;
};

struct TextureManager::VirtualTextureSpecification :
	public TextureManager::TextureSpecification {
	GLuint id = 0;
	GLuint handle = 0;
};

template <size_t SIZE>
struct TextureManager::LocalTextureSpecification :
	public TextureManager::TextureSpecification {
	std::array<std::filesystem::path, SIZE> texture_paths;
};

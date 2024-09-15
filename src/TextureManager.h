#pragma once
#include <glad/glad.h>

#include <array>
#include <filesystem>
#include <map>

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

	inline const Texture& getTexture(TextureHandle handle) const {
		auto iter = m_textures.find(handle);
		if (iter == m_textures.end())
			throw "Texture not found for handle :" + std::to_string(handle);
		return iter->second;
	}

	void releaseTexture(TextureHandle handle);

	void updateResolution(unsigned int resolutionGroup, int x, int y);
};

struct TextureManager::TextureSpecification {
	unsigned int wrapping = GL_CLAMP_TO_EDGE;
	unsigned int filtering = GL_LINEAR;

	unsigned int format = GL_RGBA;
	unsigned int internal_format = GL_RGBA;
	unsigned int encoding = GL_FLOAT;
	unsigned int type = GL_TEXTURE_2D;
	unsigned int mipmap_levels = 1;

	int target_framebuffer = -1;

	TextureHandle override = 0;
};

struct TextureManager::RuntimeTextureSpecification :
	public TextureManager::TextureSpecification {
	int width;
	int height;
	int depth;
	unsigned int resolution_group = 0;
};

struct TextureManager::VirtualTextureSpecification :
	public TextureManager::TextureSpecification {
	unsigned int id = 0;
	unsigned int handle = 0;
};

template <size_t SIZE>
struct TextureManager::LocalTextureSpecification :
	public TextureManager::TextureSpecification {
	std::array<std::filesystem::path, SIZE> texture_paths;
};

#include "TextureManager.h"

#include <stb/stb_image.h>

#include <algorithm>

#include "Texture.h"

TextureHandle TextureManager::createTexture(RuntimeTextureSpecification& specs
) {
	Texture texture;
	texture.m_textureType = specs.type;

	glGenTextures(1, &texture.m_textureID);
	glBindTexture(specs.type, texture.m_textureID);

	texture.m_width = specs.width;
	texture.m_height = specs.height;

	texture.m_format = specs.format;
	texture.m_internalFormat = specs.internal_format;

	if (specs.depth > 1)
		glTexImage3D(
			specs.type,
			0,
			specs.internal_format,
			specs.width,
			specs.height,
			specs.depth,
			0,
			specs.format,
			specs.encoding,
			specs.data.has_value() ? specs.data->data() : nullptr
		);

	else
		glTexImage2D(
			specs.type,
			0,
			specs.internal_format,
			specs.width,
			specs.height,
			0,
			specs.format,
			specs.encoding,
			specs.data.has_value() ? specs.data->data() : nullptr
		);

	glTexParameteri(specs.type, GL_TEXTURE_WRAP_S, specs.wrapping);
	glTexParameteri(specs.type, GL_TEXTURE_WRAP_T, specs.wrapping);
	if (specs.type == GL_TEXTURE_CUBE_MAP)
		glTexParameteri(specs.type, GL_TEXTURE_WRAP_R, specs.wrapping);

	glTexParameteri(
		specs.type,
		GL_TEXTURE_MIN_FILTER,
		specs.mipmap_levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : specs.filtering
	);
	glTexParameteri(specs.type, GL_TEXTURE_MAG_FILTER, specs.filtering);

	if (specs.mipmap_levels > 1) glGenerateMipmap(specs.type);

	GLuint64 textureHandle = glGetTextureHandleARB(texture.m_textureID);
	glMakeTextureHandleResidentARB(textureHandle);
	texture.m_textureBindlessHandle = textureHandle;

	if (specs.override == 0) {
		m_nextHandle++;
		m_textures[m_nextHandle] = texture;
		return m_nextHandle;
	}

	releaseTexture(specs.override);

	m_textures[specs.override] = texture;
	return specs.override;
}

TextureHandle TextureManager::createTexture(VirtualTextureSpecification& specs
) {
	Texture texture;

	texture.m_textureID = specs.handle;
	texture.m_textureBindlessHandle = specs.handle;

	texture.m_textureType = specs.type;

	texture.m_format = specs.internal_format;

	if (specs.override == 0) {
		m_nextHandle++;
		m_textures[m_nextHandle] = texture;
		return m_nextHandle;
	}

	releaseTexture(specs.override);
	m_textures[specs.override] = texture;
	return specs.override;
}
template <size_t SIZE = 1>

TextureHandle TextureManager::createTexture(
	LocalTextureSpecification<SIZE>& specs
) {
	stbi_set_flip_vertically_on_load(1);

	int textureCount = specs.texture_paths.size();

	int width, height, channels;

	unsigned char* m_data = stbi_load(
		specs.texture_paths[0].c_str(), &width, &height, &channels, 0
	);

	RuntimeTextureSpecification runtime_spec;
	runtime_spec.width = width;
	runtime_spec.height = height;
	runtime_spec.format = specs.format;
	runtime_spec.depth = specs.format == GL_TEXTURE_CUBE_MAP ? 1 : textureCount;

	TextureHandle handle = TextureManager::createTexture(runtime_spec);

	Texture& texture = m_textures[handle];

	glBindTexture(specs.type, texture.getID());

	if (textureCount > 1) {
		stbi_image_free(m_data);
		for (int i = 0; i < textureCount; i++) {
			int width, height, channels;
			unsigned char* m_data = stbi_load(
				specs.texture_paths[i].c_str(), &width, &height, &channels, 0
			);
			if (specs.type == GL_TEXTURE_CUBE_MAP)
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					specs.internal_format,
					width,
					height,
					0,
					specs.format,
					specs.encoding,
					m_data
				);
			else
				glTexSubImage3D(
					specs.type,
					0,
					0,
					0,
					0,
					texture.m_width,
					texture.m_height,
					i,
					specs.format,
					specs.encoding,
					m_data
				);

			stbi_image_free(m_data);
		}
	} else {
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			0,
			0,
			texture.m_width,
			texture.m_height,
			specs.format,
			specs.encoding,
			m_data
		);
		stbi_image_free(m_data);
	}

	return handle;
}

void TextureManager::releaseTexture(TextureHandle handle) {
	unsigned int textureID = m_textures[handle].getID();
	m_textures.erase(handle);

	for (auto textureGroup : m_resolutionGroups) {
		auto iter = std::find(
			textureGroup.second.begin(), textureGroup.second.end(), handle
		);

		// If the element is found, erase it
		if (iter != textureGroup.second.end()) {
			textureGroup.second.erase(iter);
		}
	}
	glDeleteTextures(0, &textureID);
}

void TextureManager::updateResolution(
	unsigned int resolutionGroup, int x, int y
) {
	for (TextureHandle handle : m_resolutionGroups[resolutionGroup]) {
		Texture& old = m_textures[handle];

		VirtualTextureSpecification specs {
			.id = old.getID(),
			.handle = old.getHandle(),
		};

		specs.override = handle;
		createTexture(specs);
	}
};
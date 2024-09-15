#pragma once

#include <memory>

#include "Material.h"
#include "Program.h"
#include "ResourceTypes.h"
#include "TextureManager.h"
#include "scene/MaterialDescription.h"

struct UBO {};

struct StandardMaterialUBO : public UBO {
	unsigned int albedo;
};

struct MVP_UBO : public UBO {
	glm::mat4 u_model;
	glm::mat4 u_view;
	glm::mat4 u_projection;
};

class ResourceManager {
private:
	TextureManager m_textureManager;

	MaterialHandle m_nextMaterialHandle = 1;
	MaterialHandle m_nextProgramHandle = 1;
	MaterialHandle m_nextUBOHandle = 1;

	std::map<MaterialHandle, Material> m_materials;
	std::map<ProgramHandle, Program> m_programs;
	std::map<UBOHandle, unsigned int> m_ubos;

	std::map<std::filesystem::path, ProgramHandle> m_programCache;

protected:
	ProgramHandle registerProgram(
		const std::filesystem::path vertex, const std::filesystem::path fragment
	);

public:
	inline TextureManager& getTextureManager() { return m_textureManager; }

	MaterialHandle registerMaterial(Material material);

	template <typename T>
	MaterialHandle registerUBO(T ubo);

	inline unsigned int getUBO(UBOHandle handle) { return m_ubos[handle]; }
};

#pragma once

#include <memory>

#include "Material.h"
#include "Program.h"
#include "ResourceTypes.h"
#include "TextureManager.h"
#include "VertexBuffer.h"

class ResourceManager {
public:
	enum class DefaultUBOType {
		ViewProjection,
		Lights,
	};
	class UBOs;

private:
	TextureManager m_textureManager;

	ProgramHandle m_defaultProgram;

	MaterialHandle m_nextMaterialHandle = 1;
	MaterialHandle m_nextProgramHandle = 1;
	MaterialHandle m_nextUBOHandle = 1;

	std::map<MaterialHandle, Material> m_materials;
	std::map<ProgramHandle, Program> m_programs;
	std::map<UBOHandle, unsigned int> m_ubos;
	std::map<DefaultUBOType, UBOHandle> m_uboTypes;

	std::map<std::filesystem::path, ProgramHandle> m_programCache;

	std::shared_ptr<VertexBuffer> m_staticVBO;

protected:
public:
	ResourceManager();

	inline TextureManager& getTextureManager() { return m_textureManager; }

	MaterialHandle registerMaterial(Material material);
	inline Material& getMaterial(MaterialHandle handle) {
		return m_materials[handle];
	}

	ProgramHandle registerProgram(
		const std::filesystem::path vertex, const std::filesystem::path fragment
	);
	inline ProgramHandle getDefaultProgramHandle() { return m_defaultProgram; }
	inline Program& getProgram(ProgramHandle handle) {
		return m_programs[handle];
	}

	template <typename T>
	UBOHandle registerUBO(T ubo);

	inline UBOHandle getDefaultUBO(DefaultUBOType type) {
		return m_uboTypes[type];
	}

	inline unsigned int getUBO(UBOHandle handle) { return m_ubos[handle]; }

	inline std::shared_ptr<VertexBuffer> getStaticVBO() { return m_staticVBO; }
};

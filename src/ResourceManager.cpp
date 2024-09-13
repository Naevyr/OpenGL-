#include "ResourceManager.h"

#include <filesystem>

#include "Material.h"
#include "Program.h"
#include "ResourceTypes.h"
#include "TextureManager.h"
#include "scene/MaterialDescription.h"

MaterialHandle ResourceManager::registerMaterial(
	StandardMaterialDescription desc
) {
	TextureManager::LocalTextureSpecification<1> specs;

	StandardMaterial material;

	specs.texture_paths = { desc.albedo.value_or("") };
	material.albedo = m_textureManager.createTexture(specs);

	specs.texture_paths = { desc.albedo.value_or("") };
	material.normal = m_textureManager.createTexture(specs);

	material.program =
		registerProgram(Program::STANDARD::VERTEX, Program::STANDARD::FRAGMENT);

	MaterialHandle handle = m_nextMaterialHandle;

	m_nextMaterialHandle++;

	m_materials[handle] = material;

	return handle;
}

ProgramHandle ResourceManager::registerProgram(
	const std::filesystem::path vertex, const std::filesystem::path fragment
) {
	if (m_programCache.find(vertex) != m_programCache.end())
		return m_programCache[vertex];

	ProgramHandle handle = m_nextProgramHandle;

	m_nextMaterialHandle++;

	m_programs[handle] = Program(vertex, fragment);
	m_programCache[vertex] = handle;

	return handle;
}
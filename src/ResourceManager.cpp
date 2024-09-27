#include "ResourceManager.h"

#include <filesystem>
#include <memory>

#include "Light.h"
#include "Material.h"
#include "Primitive.h"
#include "Program.h"
#include "ResourceTypes.h"
#include "glad/glad.h"

ResourceManager::ResourceManager() {
	m_defaultProgram = registerProgram(
		Program::DefaultPrograms::STANDARD_FORWARD::VERTEX,
		Program::DefaultPrograms::STANDARD_FORWARD::FRAGMENT
	);

	UBOHandle handle;

	Light::UniformBuffer lightUBO;
	handle = registerUBO(lightUBO);
	m_uboTypes[DefaultUBOType::Lights] = handle;

	Primitive::ViewProjectionUniformBuffer vpUBO;
	handle = registerUBO(vpUBO);
	m_uboTypes[DefaultUBOType::ViewProjection] = handle;
};

MaterialHandle ResourceManager::registerMaterial(Material material) {
	MaterialHandle handle = m_nextMaterialHandle;

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

template <typename T>
UBOHandle ResourceManager::registerUBO(T ubo) {
	unsigned int binding;
	glGenBuffers(1, &binding);
	glBindBuffer(GL_UNIFORM_BUFFER, binding);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &binding, GL_DYNAMIC_DRAW);

	UBOHandle handle = m_nextUBOHandle;
	m_nextUBOHandle++;

	m_ubos[handle] = binding;

	return handle;
}

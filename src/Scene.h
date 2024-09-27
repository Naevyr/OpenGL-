#pragma once

#include <tiny_gltf.h>

#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "Node.h"
#include "Primitive.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "scene/EnvironmentDescription.h"
#include "scene/SceneDescription.h"

class Scene {
private:
	std::vector<NodeID> m_primitives;
	std::vector<NodeID> m_lights;

	std::map<NodeID, std::unique_ptr<Node>> m_nodes;

	NodeID m_rootNode;

	NodeID m_Camera;
	NodeID m_nextNodeID = 1;
	EnvironmentDescription m_Environment;

	NodeID loadNode(
		tinygltf::Node& baseNode,
		std::vector<tinygltf::Node>& scene,
		NodeID parent = 0
	);

	NodeID loadMesh(
		tinygltf::Mesh& mesh,
		tinygltf::Model& data,
		ResourceManager& resourceManager,
		std::unordered_map<unsigned int, MaterialHandle>& materialCache
	);

	std::unordered_map<unsigned int, TextureHandle> loadTextures(
		tinygltf::Model& data, ResourceManager& resourceManager
	);
	std::unordered_map<unsigned int, MaterialHandle> loadMaterials(
		tinygltf::Model& data,
		ResourceManager& resourceManager,
		std::unordered_map<unsigned int, TextureHandle>& textures
	);

public:
	Scene(
		SceneDescription description,
		std::shared_ptr<ResourceManager> resourceManager
	);

	inline void setEnvironment(EnvironmentDescription environment) {
		m_Environment = environment;
	}
	inline EnvironmentDescription& getEnvironment() { return m_Environment; }
	inline Camera& getCamera() { return (Camera&)m_nodes[m_Camera]; }

	std::vector<std::reference_wrapper<Light>> getLights();
	std::vector<std::reference_wrapper<Mesh>> getMeshes();
};
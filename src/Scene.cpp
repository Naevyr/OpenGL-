#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <span>
#include <unordered_map>
#include <vector>

#include "Node.h"
#include "Primitive.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
#include "TextureManager.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

// Define these only in *one* .cc file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tinygltf/tiny_gltf.h"

Scene::Scene(
	SceneDescription scene, std::shared_ptr<ResourceManager> textureManager
) {
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool ret =
		loader.LoadASCIIFromFile(&model, &err, &warn, scene.gltf_path.c_str());

	if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Err: %s\n", err.c_str());
	}

	if (!ret) {
		printf("Failed to parse glTF\n");
	}

	auto vbo = std::make_shared<VertexBuffer>();

	loadNode(model.nodes[0], model.nodes);
}

NodeID Scene::loadNode(
	tinygltf::Node& baseNode, std::vector<tinygltf::Node>& scene, NodeID parent
) {
	// Deferred loading of meshes
	if (baseNode.mesh != -1) return 0;

	NodeID id = m_nextNodeID;
	m_nextNodeID++;

	m_nodes[id] = std::make_unique<Node>(id, parent);
	Node& node = *m_nodes[id];

	node.setPosition(glm::vec3(
		baseNode.translation[0],
		baseNode.translation[1],
		baseNode.translation[2]
	));

	node.setScale(
		glm::vec3(baseNode.scale[0], baseNode.scale[1], baseNode.scale[2])
	);

	node.setOrientation(glm::quat(
		baseNode.rotation[0],
		baseNode.rotation[1],
		baseNode.rotation[2],
		baseNode.rotation[3]
	));

	if (parent != 0) m_nodes[parent]->addChild(id);

	for (auto baseChildID : baseNode.children) {
		loadNode(scene[baseChildID], scene, id);
	}

	return id;
}

NodeID Scene::loadMesh(
	tinygltf::Mesh& mesh,
	tinygltf::Model& data,
	ResourceManager& resourceManager,
	std::unordered_map<unsigned int, MaterialHandle>& materialCache
) {
	std::vector<NodeID> primitive;
	NodeID id = m_nextNodeID;
	m_nextNodeID++;

	for (auto baseMaterial : data.materials) {
		data.images[data.textures[baseMaterial.pbrMetallicRoughness
		                              .baseColorTexture.index]
		                .source]
			.bits;
	}

	for (auto basePrimitive : mesh.primitives) {
		NodeID primitiveID = m_nextNodeID;
		m_nextNodeID++;

		tinygltf::BufferView& bufferView =
			data.bufferViews[data.accessors[basePrimitive.indices].bufferView];
		std::span<unsigned char> indices(
			data.buffers[bufferView.buffer].data.data() + bufferView.byteOffset,
			bufferView.byteLength
		);

		if (basePrimitive.attributes.size() != 3)
			throw "Only POSITION, NORMAL, TEXCOORD attributes supported, please load a mesh which has  exclusively those attributes";

		tinygltf::BufferView& positionBufferView =
			data.bufferViews
				[data.accessors[basePrimitive.attributes["POSITION"]]
		             .bufferView];

		tinygltf::Buffer& positionBuffer =
			data.buffers[positionBufferView.buffer];

		auto positionBufferIter =
			positionBuffer.data.begin() + positionBufferView.byteOffset;

		tinygltf::BufferView& normalBufferView =
			data.bufferViews[data.accessors[basePrimitive.attributes["NORMAL"]]
		                         .bufferView];

		tinygltf::Buffer& normalBuffer = data.buffers[normalBufferView.buffer];
		auto normalBufferIter =
			normalBuffer.data.begin() + normalBufferView.byteOffset;

		tinygltf::BufferView& textureBufferView =
			data.bufferViews
				[data.accessors[basePrimitive.attributes["TEXCOORD_0"]]
		             .bufferView];
		tinygltf::Buffer& textureBuffer =
			data.buffers[textureBufferView.buffer];

		auto textureBufferIter =
			textureBuffer.data.begin() + normalBufferView.byteOffset;

		std::vector<unsigned char> vertices;
		vertices.reserve(
			positionBufferView.byteLength + normalBufferView.byteLength +
			textureBufferView.byteLength
		);

		for (int vertexCount = 0;
		     vertexCount < positionBufferView.byteLength / 8;
		     vertexCount++) {
			vertices.insert(
				vertices.end(),
				positionBufferIter +
					positionBufferView.byteStride * vertexCount * 12,
				positionBufferIter +
					positionBufferView.byteStride * vertexCount * 12 + 12
			);
			vertices.insert(
				vertices.end(),
				normalBufferIter +
					normalBufferView.byteStride * vertexCount * 12,
				normalBufferIter +
					normalBufferView.byteStride * vertexCount * 12 + 12
			);
			vertices.insert(
				vertices.end(),
				textureBufferIter +
					textureBufferView.byteStride * vertexCount * 8,
				textureBufferIter +
					textureBufferView.byteStride * vertexCount * 8 + 8
			);
		}

		VertexArray::Specifications specs {
			.vertices = vertices,
			.indices = indices,
			.vertexBuffer = resourceManager.getStaticVBO()
		};
		VertexArray vao = VertexArray(specs);

		m_nodes[primitiveID] = std::make_unique<Primitive>(
			vao, materialCache[basePrimitive.material], primitiveID, id
		);
	}
}

std::unordered_map<unsigned int, TextureHandle> Scene::loadTextures(
	tinygltf::Model& data, ResourceManager& resourceManager
) {
	std::unordered_map<unsigned int, TextureHandle> textureCache;
	textureCache.reserve(data.images.size());

	for (int i = 0; i < data.textures.size(); i++) {
		tinygltf::Texture texture = data.textures[i];
		tinygltf::Image& image = data.images[texture.source];

		TextureManager::RuntimeTextureSpecification specs = {
			.height = image.height,
			.width = image.width,
			.data = image.image,
		};
		GLenum format;

		switch (image.component) {
			case 1:
				format = GL_RED;
				break;
			case 2:
				format = GL_RG;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				format = GL_RGB;
		}
		specs.internal_format = format;
		specs.format = format;
		specs.encoding =
			image.pixel_type == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE
				? GL_UNSIGNED_BYTE
				: GL_UNSIGNED_SHORT;

		TextureHandle handle =
			resourceManager.getTextureManager().createTexture(specs);

		textureCache[i] = handle;
	}

	return textureCache;
}

std::unordered_map<unsigned int, MaterialHandle> Scene::loadMaterials(
	tinygltf::Model& data,
	ResourceManager& resourceManager,
	std::unordered_map<unsigned int, TextureHandle>& textures
) {
	std::unordered_map<unsigned int, MaterialHandle> materialCache;

	ProgramHandle defaultProgram = resourceManager.getDefaultProgramHandle();

	for (int i = 0; i < data.materials.size(); i++) {
		tinygltf::Material baseMaterial = data.materials[i];

		UBOHandle viewProjection = resourceManager.getDefaultUBO(
			ResourceManager::DefaultUBOType::ViewProjection
		);

		Material material = Material::StandardMaterial(
			defaultProgram,
			textures[baseMaterial.pbrMetallicRoughness.baseColorTexture.index],
			textures[baseMaterial.normalTexture.index],
			textures[baseMaterial.pbrMetallicRoughness.metallicRoughnessTexture
		                 .index],
			0,
			0,
			textures[baseMaterial.emissiveTexture.index],
			viewProjection
		);
		MaterialHandle handle = resourceManager.registerMaterial(material);
		materialCache[i] = handle;
	}

	return materialCache;
}

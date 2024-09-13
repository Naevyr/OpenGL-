#pragma once

#include <optional>
#include <vector>

#include "CameraDescription.h"
#include "scene/EnvironmentDescription.h"
#include "scene/LightDescription.h"
#include "scene/MeshDescription.h"

struct SceneDescription {
	std::string gltf_path;
	std::vector<MeshDescription> additional_meshes;
	std::vector<LightDescription> additional_lights;

	std::optional<EnvironmentDescription> environment;
	CameraDescription camera;
};

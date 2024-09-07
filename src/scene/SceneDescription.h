#pragma once 

#include "CameraDescription.h"
#include "scene/LightDescription.h"
#include "scene/MeshDescription.h"
#include "scene/EnvironmentDescription.h"

#include <optional>
#include <vector>


struct SceneDescription
{       
    std::string gltf_path;
    std::vector<MeshDescription> additional_meshes;
    std::vector<LightDescription> additional_lights;
    
    
    std::optional<EnvironmentDescription> environment;
    CameraDescription camera;
};

#pragma once 

#include "scene/LightDescription.h"
#include "scene/MeshDescription.h"
#include "scene/EnvironmentDescription.h"


struct SceneDescription
{       
    std::string gltf_path;
    std::vector<MeshDescription> additional_meshes;
    std::vector<LightDescription> additional_lights;

    
    EnvironmentDescription environment;
};

#pragma once

#include "Texture.h"
#include "Scene.h"


#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <MaterialDefinition.h>



struct RenderSpecifications;
class Pipeline {
  
    public:
        virtual void Initialize() = 0;
        virtual void Render(Scene& scene, RenderSpecifications& specs) = 0;
        

        //Every pipeline should their own implementation of a material
        virtual unsigned int LoadMaterial(MaterialDefinition materialDefs, std::unordered_map<std::string, unsigned int>& local_textures,  std::vector<Texture>& global_textures) = 0;
};




struct RenderSpecifications {
    glm::mat4 projection;
    glm::mat4 view;
    int width;
    int height;
};
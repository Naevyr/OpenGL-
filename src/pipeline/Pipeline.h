#pragma once

#include "Texture.h"
#include "Scene.h"


#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>



struct RenderSpecifications;
class Pipeline {
  
    public:
        virtual void Render(RenderSpecifications& specs) = 0;
        

        //Every pipeline should their own implementation of a material
        //virtual unsigned int LoadMaterial(MaterialDescrip materialDefs, std::unordered_map<std::string, unsigned int>& local_textures,  std::vector<Texture>& global_textures) = 0;
};




struct RenderSpecifications {

    Scene& scene;
    glm::mat4 projection;
    glm::mat4 view;

    Texture& colorTexture;
    Texture& depthTexture;
};
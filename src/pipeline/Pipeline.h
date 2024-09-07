#pragma once


#include "Renderer.h"
#include "Scene.h"
#include "TextureAllocator.h"
#include <glm/glm.hpp>

class Pipeline {

    public:

        
        struct RenderSpecifications;


    protected:

        Pipeline();
        unsigned int m_ShadowFB;
        TextureHandle m_shadowMap;
        
        

        unsigned int m_nextMaterialHandle = 0;


        void renderShadowMap(Scene& scene);


    public:
        virtual void render(RenderSpecifications& specs) = 0;
        virtual void setup(Renderer::RenderFeatures features);

        virtual MaterialHandle registerMaterial(MaterialDescription& description);


        //Every pipeline should their own implementation of a material
        //virtual unsigned int LoadMaterial(MaterialDescrip materialDefs, std::unordered_map<std::string, unsigned int>& local_textures,  std::vector<Texture>& global_textures) = 0;
};




struct Pipeline::RenderSpecifications {

    Scene& scene;

    
    glm::mat4 projection;
    glm::mat4 view;

    TextureHandle colorTexture;
    TextureHandle depthTexture;
};
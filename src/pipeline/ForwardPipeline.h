#pragma once
#include "pipeline/Pipeline.h"
#include "Material.h"
#include "Light.h"
#include "scene/EnvironmentDescription.h"
#include "TextureAllocator.h"

#include <memory>
#include <vector>


class ForwardPipeline : public Pipeline {


    private:

        

   
        unsigned int m_ColorFB;
        unsigned int m_LightUBO;
        



        TextureHandle m_shadowMap;

        Material m_shadowMaterial;

        std::vector<Material> m_materials;
        
        std::weak_ptr<TextureAllocator> m_textureAllocator;

        
        void setLightUniform(std::vector<Light>& lights, EnvironmentDescription& environment);
        void setTransformUniform(glm::mat4 projection, glm::mat4 view);


    public:


        inline ForwardPipeline() { }
        
        ForwardPipeline( std::shared_ptr<TextureAllocator> textureAllocator);

        void render(RenderSpecifications& specs) override; 
        void setup(Renderer::RenderFeatures renderFeatures) override;


        inline ~ForwardPipeline() {}
};


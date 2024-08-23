#pragma once
#include "Pipeline.h"
#include "Material.h"
#include "Light.h"
#include "scene/EnvironmentDescription.h"
#include "TextureAllocator.h"

#include <vector>
class ForwardPipeline : public Pipeline{


    private:

        

        unsigned int m_ShadowFB;
        unsigned int m_ColorFB;
        unsigned int m_LightUBO;
        



        TextureHandle m_shadowMap;

        Material m_shadowMaterial;

        std::vector<Material> m_materials;
        
        std::shared_ptr<TextureAllocator> m_textureAllocator;

        
        void SetLightUniform(std::vector<Light>& lights, EnvironmentDescription& environment);
        void SetTransformUniform(glm::mat4 projection, glm::mat4 view);
        void RenderShadowMap(Scene& scene);
      

    public:


        inline ForwardPipeline() { }
        
        ForwardPipeline(std::shared_ptr<TextureAllocator> textureAllocator);

        void Render(RenderSpecifications& specs) override; 
        
        inline ~ForwardPipeline() {}
};


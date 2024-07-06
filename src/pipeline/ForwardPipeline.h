#pragma once
#include "Pipeline.h"
#include "Material.h"
#include "Light.h"
#include "Environment.h"

#include <vector>
class ForwardPipeline : public Pipeline{


    private:

        

        unsigned int m_ShadowFB;
        unsigned int m_ShadowMap;
        

        unsigned int m_ColorFB;

        unsigned int m_LightUBO;
        


        int m_shadowMapTextureIndex = -1;

        Material m_shadowMaterial;
        std::vector<Material> m_materials;
        


        
        void SetLightUniform(std::vector<Light>& lights, Environment& environment);
        void SetTransformUniform(glm::mat4 projection, glm::mat4 view);
      

    public:

        inline ForwardPipeline() {}
        void Initialize() override;
        void Render(Scene& scene, RenderSpecifications& specs) override; 
        

        unsigned int LoadMaterial(MaterialDefinition materialDefinition, std::unordered_map<std::string, unsigned int>& local_textures,  std::vector<Texture>& global_textures) override;

        void RenderShadowMap(Scene& scene);
        
        inline ~ForwardPipeline() {}
};


#pragma once

#include "Scene.h"
#include "Material.h"
#include "pipeline/ForwardPipeline.h"
#include <unordered_map>
#include <string>
#include "postprocessing/HDRBloom.h"
#include "postprocessing/Blur.h"
#include "postprocessing/PostProcessingEffects.h"




class Renderer {
    private: 

        ForwardPipeline m_pipeline;

        std::vector<Material> m_materials;
        std::vector<Texture> m_textures;
        std::unordered_map<std::string, unsigned int> m_loadedTextureMap;


        int m_framebufferColor;
        int m_temporaryBuffer;
        int m_framebufferDepth;

        
        HDRBloom m_bloom;
        Blur m_blur;

        glm::mat4 m_Projection, m_View;


        int m_Width, m_Height;


        unsigned int m_LightBuffer;




        unsigned int m_FirstPassFBO;

        

        Material m_quadMaterial;
        unsigned int m_quadVAO;





        void SetTransformUniform(glm::mat4 projection, glm::mat4 view);
        void SetLightUniform(std::vector<Light>& lights, Environment& environment);
        void SetShadowMapUniform(Scene& scene);

        void RenderShadowMap(Scene& scene);
        void DrawQuad(Texture &texture);
    public:

        inline Renderer() { };
        

        void Init(int width, int height);
        void Render(Scene &scene, PostProcessingEffects &effects);
        void SetResolution(int width, int height);

        Texture& LoadTexture(std::string file_path);
        Texture& LoadTextureArray(std::string file_paths[]);
        Texture& LoadCubeMap(std::string folder_path);
        inline Texture& GetTexture(unsigned int index) { return m_textures[index]; }

        unsigned int LoadMaterial(MaterialDescription materialDefinition);
        unsigned int LoadSkyboxMaterial(std::string cubemapFolder);

        inline ~Renderer() { };
};
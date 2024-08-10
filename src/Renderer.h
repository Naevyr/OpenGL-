#pragma once

#include "Scene.h"
#include "Material.h"
#include "pipeline/ForwardPipeline.h"
#include <unordered_map>
#include <string>
#include "postprocessing/HDRBloom.h"
#include "postprocessing/Blur.h"
#include "postprocessing/PostProcessingEffects.h"
#include "scene/SceneDescription.h"



class Renderer {
    private: 
        
        ForwardPipeline m_pipeline;


        int m_framebufferColor;
        int m_framebufferDepth;
        int m_temporaryBuffer;


        std::unique_ptr<TextureAllocator> m_textureAllocator;



        HDRBloom m_bloom;
        glm::mat4 m_Projection, m_View;


        int m_Width, m_Height;


        unsigned int m_mainPassFBO;
        unsigned int m_quadVAO;

        void SetTransformUniform(glm::mat4 projection, glm::mat4 view);
        void DrawQuad(Texture &texture);


    public:

        inline Renderer() { };
        Renderer(int width, int height);
        

        
        void SetScene(SceneDescription &scene);
        void SetResolution(int width, int height);
        



        void Render();

};
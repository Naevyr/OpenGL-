#pragma once

#include "Scene.h"
#include "Material.h"
#include "pipeline/ForwardPipeline.h"

#include "postprocessing/HDRBloom.h"

#include "scene/SceneDescription.h"


class Renderer {

    public:
        enum class RenderFeatures;


    private: 
        
        ForwardPipeline m_pipeline;
        TextureAllocator m_textureAllocator;




        TextureHandle m_framebufferColor;
        TextureHandle m_framebufferDepth;
        TextureHandle m_temporaryBuffer;





        HDRBloom m_bloom;

        
        glm::mat4 m_projection, m_view;


        int m_width, m_height;


        unsigned int m_mainPassFBO;


        static unsigned int s_quadVAO;
        static Material s_quadMaterial;


    public:

        inline Renderer() { };
        Renderer(int width, int height);
        

        
        void setScene(SceneDescription &scene);
        void setResolution(int width, int height);
        



        void Render();

        static void DrawQuad(Texture &texture);
};


enum class Renderer::RenderFeatures {
    RENDER_FEATURE_LIGHTING = 1 << 0,
    RENDER_FEATURE_SHADOWS = 1 << 1,
    RENDER_FEATURE_SKYBOX = 1 << 2,
};
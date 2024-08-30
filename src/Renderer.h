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
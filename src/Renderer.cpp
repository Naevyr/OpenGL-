
#include "Renderer.h"

#include "scene/EnvironmentDescription.h"
#include "pipeline/Pipeline.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>


#include <array>

Renderer::Renderer(int width, int height) {
    


    setResolution(width, height);


    



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
    glDepthMask(GL_TRUE);


    m_textureAllocator = TextureAllocator();


    m_pipeline = ForwardPipeline(m_textureAllocator);


  
    
    m_bloom = HDRBloom(m_textureAllocator);
    
    
    RuntimeTextureSpecs framebufferSpecs;
    framebufferSpecs.width = 800;
    framebufferSpecs.height = 600;
    framebufferSpecs.internal_format = GL_RGBA32F;
    framebufferSpecs.encoding = GL_FLOAT;


    m_framebufferColor = m_textureAllocator.createTexture(framebufferSpecs);
    m_temporaryBuffer = m_textureAllocator.createTexture(framebufferSpecs);
    


    RuntimeTextureSpecs depth_specs;

    depth_specs.type = GL_TEXTURE_2D;
    depth_specs.width = 800;
    depth_specs.height = 600;
    depth_specs.filtering = GL_NEAREST;
    depth_specs.format = GL_DEPTH_COMPONENT;
    depth_specs.internal_format = GL_DEPTH_COMPONENT;

    m_framebufferDepth = m_textureAllocator.createTexture(depth_specs);



    glGenFramebuffers(1, &m_mainPassFBO);


}


void Renderer::Render(Scene& scene, PostProcessingEffects& effects) {


    Texture& fbColor = m_textureAllocator.getTexture(m_framebufferColor);
    Texture& fbDepth = m_textureAllocator.getTexture(m_framebufferDepth);
    Texture& tmp = m_textureAllocator.getTexture(m_temporaryBuffer);


    glBindFramebuffer(GL_FRAMEBUFFER, m_mainPassFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbColor.getID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbDepth.getID(), 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_View = scene.GetCamera().getOrientation() * glm::translate(glm::mat4(1), scene.GetCamera().getPosition());    
    RenderSpecifications specs = {
        
        .scene = scene,
        .projection = m_projection,
        .view = m_View,
        .colorTexture = m_framebufferColor,
        .depthTexture = m_framebufferDepth,
    };

    
    m_pipeline.Render(specs);


    glBindFramebuffer(GL_FRAMEBUFFER, m_mainPassFBO);
    glBindTexture(GL_TEXTURE_2D, fbColor.getID());
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,fbColor.getID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbDepth.getID(), 0);


    Mesh skybox = scene.GetEnvironment().skybox;

   
    auto skyboxMaterial = m_materials[skybox.getMaterialIndex()];
    skyboxMaterial.Bind();
    skyboxMaterial.SetUniform<glm::mat4>("u_Projection", m_projection);
    skyboxMaterial.SetUniform<glm::mat4>("u_View", m_View);
    skybox.Draw(skyboxMaterial);

    
    if(effects.bloom){

        m_bloom.Run(m_textureAllocator.getTexture(m_framebufferColor), m_textureAllocator.getTexture(m_temporaryBuffer));
        glCopyImageSubData( tmp.getID(), GL_TEXTURE_2D, 0 , 0, 0, 0,
                fbColor.getID(), GL_TEXTURE_2D,  0, 0, 0, 0,
                fbColor.getWidth() , fbColor.getHeight(), 1);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    Renderer::DrawQuad(m_textureAllocator.getTexture(m_framebufferColor));
}




void Renderer::setResolution(int width, int height)
{
    m_width = width;
    m_height = height;
    m_projection = glm::perspective(glm::radians(45.0f), (float) width / height, 0.1f, 1000.0f);

}






void Renderer::DrawQuad(Texture &texture) {

    if(s_quadVAO == 0)
    {
        s_quadMaterial = Material("resources/shaders/quad.vert", "resources/shaders/quad.frag");
        glGenVertexArrays(1,&s_quadVAO);
    }

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(s_quadVAO);
    s_quadMaterial.SetUniform<Texture&>("u_Texture", texture);
    s_quadMaterial.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


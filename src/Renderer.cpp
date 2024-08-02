
#include "Renderer.h"

#include "Environment.h"
#include "pipeline/Pipeline.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>


#include <array>

void Renderer::Init(int width, int height) {
    
    SetResolution(width, height);


   



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
    glDepthMask(GL_TRUE);



    m_pipeline = ForwardPipeline();

    m_pipeline.Initialize();


    m_textures.reserve(10);
    
    m_bloom.Initialize();
    m_blur.Initialize();
    
    RuntimeTextureSpecs framebufferSpecs;
    framebufferSpecs.width = 800;
    framebufferSpecs.height = 600;
    framebufferSpecs.internal_format = GL_RGBA32F;
    framebufferSpecs.encoding = GL_FLOAT;


    m_textures.push_back(
        Texture::CreateTexture(framebufferSpecs)
    );


    m_framebufferColor = m_textures.size() - 1;


    RuntimeTextureSpecs depth_specs;

    depth_specs.type = GL_TEXTURE_2D;
    depth_specs.width = 800;
    depth_specs.height = 600;
    depth_specs.filtering = GL_NEAREST;
    depth_specs.format = GL_DEPTH_COMPONENT;
    depth_specs.internal_format = GL_DEPTH_COMPONENT;

    m_textures.push_back(
        Texture::CreateTexture(depth_specs)
    );
    m_framebufferDepth = m_textures.size() - 1;

    glGenFramebuffers(1, &m_FirstPassFBO);


    RuntimeTextureSpecs framebufferSpecs2;
    framebufferSpecs2.width = 800;
    framebufferSpecs2.height = 600;
    framebufferSpecs2.internal_format = GL_RGBA32F;
    framebufferSpecs2.encoding = GL_FLOAT;


    m_textures.push_back(
        Texture::CreateTexture(framebufferSpecs2)
    );

    m_temporaryBuffer = m_textures.size() - 1;

    m_quadMaterial = Material("resources/shaders/quad.vert", "resources/shaders/quad.frag");
    glGenVertexArrays(1,&m_quadVAO);
}


void Renderer::Render(Scene& scene, PostProcessingEffects& effects) {

    glBindFramebuffer(GL_FRAMEBUFFER, m_FirstPassFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textures[m_framebufferColor].GetTextureID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textures[m_framebufferDepth].GetTextureID(), 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_View = scene.GetCamera().getOrientation() * glm::translate(glm::mat4(1), scene.GetCamera().getPosition());    
    RenderSpecifications specs = {
        m_Projection,
        m_View,
        m_textures[m_framebufferColor],
        m_textures[m_framebufferDepth],
    };

    
    m_pipeline.Render(scene,specs);


    glBindFramebuffer(GL_FRAMEBUFFER, m_FirstPassFBO);
    glBindTexture(GL_TEXTURE_2D, m_textures[m_framebufferColor].GetTextureID());
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textures[m_framebufferColor].GetTextureID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textures[m_framebufferDepth].GetTextureID(), 0);


    Mesh skybox = scene.GetEnvironment().skybox;

   
    auto skyboxMaterial = m_materials[skybox.getMaterialIndex()];
    skyboxMaterial.Bind();
    skyboxMaterial.SetUniform<glm::mat4>("u_Projection", m_Projection);
    skyboxMaterial.SetUniform<glm::mat4>("u_View", m_View);
    skybox.Draw(skyboxMaterial);
    if(effects.bloom){

        m_bloom.Run(m_textures[m_framebufferColor], m_textures[m_temporaryBuffer]);
        glCopyImageSubData( m_textures[m_temporaryBuffer].GetTextureID(), GL_TEXTURE_2D, 0 , 0, 0, 0,
                m_textures[m_framebufferColor].GetTextureID(), GL_TEXTURE_2D,  0, 0, 0, 0,
                m_textures[m_framebufferColor].GetWidth() , m_textures[m_framebufferColor].GetHeight(), 1);
    }
    
    DrawQuad(m_textures[m_framebufferColor]);
}




void Renderer::SetResolution(int width, int height)
{
    m_Width = width;
    m_Height = height;
    m_Projection = glm::perspective(glm::radians(45.0f), (float) width / height, 0.1f, 1000.0f);

}




unsigned int Renderer::LoadSkyboxMaterial(std::string cubemapFolder ) {


    auto material = Material("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");

    
    material.SetUniform<Texture&>("u_Skybox",LoadCubeMap(cubemapFolder));
    
    m_materials.push_back(material);

    return m_materials.size() - 1;
}


unsigned int Renderer::LoadMaterial(MaterialDescription defs) 
{
    return m_pipeline.LoadMaterial(defs, m_loadedTextureMap, m_textures);
}



Texture& Renderer::LoadCubeMap(std::string folder_path) 
{
    
    std::array<std::string,6> file_paths = {
        "/right.png", "/left.png", "/bottom.png", "/top.png", "/front.png", "/back.png"
    };

    
    for (size_t i = 0; i < 6; i++)
    {
        file_paths[i] = folder_path  + file_paths[i];
    }
    LocalTextureSpecs<6> specs;
    specs.path = file_paths;
    specs.format = GL_RGBA;
    specs.type = GL_TEXTURE_CUBE_MAP;


    Texture texture = Texture::CreateTexture(specs);
    m_textures.push_back(texture);

    return m_textures.back();
}



Texture& Renderer::LoadTexture(std::string path) {


    if(m_loadedTextureMap.find(path) != m_loadedTextureMap.end())
        return m_textures[m_loadedTextureMap[path]];

    

    LocalTextureSpecs<1> specs;
    specs.path = {path};
    specs.format = GL_RGB;
    specs.type = GL_TEXTURE_2D;

    auto texture = Texture::CreateTexture(specs);

    m_textures.push_back(texture);
   
    m_loadedTextureMap[path] = m_textures.size() - 1;


    return m_textures.back();
}

void Renderer::DrawQuad(Texture &texture) {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(m_quadVAO);
    m_quadMaterial.SetUniform<Texture&>("u_Texture", texture);
    m_quadMaterial.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


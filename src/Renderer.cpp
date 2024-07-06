
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
    
    m_bloom = HDRBloom("resources/shaders/c_bloom.glsl");

    m_textures.push_back(
        Texture::CreateTexture(800,600,4)
    );


    m_firstPassTexture = m_textures.size() - 1;


    unsigned int depthTexture;
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    m_textures.push_back(
        Texture::CreateTexture(depthTexture, GL_TEXTURE_2D)
    );
    m_firstPassDepth = m_textures.size() - 1;

    glGenFramebuffers(1, &m_FirstPassFBO);
}


void Renderer::Render(Scene& scene) {

    glBindFramebuffer(GL_FRAMEBUFFER, m_FirstPassFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textures[m_firstPassTexture].GetTextureID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textures[m_firstPassDepth].GetTextureID(), 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_View = scene.GetCamera().getOrientation() * glm::translate(glm::mat4(1), scene.GetCamera().getPosition());    
    RenderSpecifications specs = {
        m_Projection,
        m_View,
        m_textures[m_firstPassTexture],
        m_textures[m_firstPassDepth],
    };

    
    m_pipeline.Render(scene,specs);


    glBindFramebuffer(GL_FRAMEBUFFER, m_FirstPassFBO);
    glBindTexture(GL_TEXTURE_2D, m_textures[m_firstPassTexture].GetTextureID());
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textures[m_firstPassTexture].GetTextureID(), 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textures[m_firstPassDepth].GetTextureID(), 0);


    Mesh skybox = scene.GetEnvironment().skybox;

   
    auto skyboxMaterial = m_materials[skybox.getMaterialIndex()];
    skyboxMaterial.Use();
    skyboxMaterial.SetUniform<glm::mat4>("u_Projection", m_Projection);
    skyboxMaterial.SetUniform<glm::mat4>("u_View", m_View);
    skybox.Draw(skyboxMaterial);
    
    
    m_bloom.Run(m_textures[m_firstPassTexture],m_textures[m_firstPassTexture]);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FirstPassFBO); 
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

}




void Renderer::SetResolution(int width, int height)
{
    m_Width = width;
    m_Height = height;
    m_Projection = glm::perspective(glm::radians(45.0f), (float) width / height, 0.1f, 1000.0f);

}




unsigned int Renderer::LoadSkyboxMaterial(std::string cubemapFolder ) {


    auto material = Material("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");

    
    material.SetTexture("u_Skybox",LoadCubeMap(cubemapFolder));
    
    m_materials.push_back(material);

    return m_materials.size() - 1;
}


unsigned int Renderer::LoadMaterial(MaterialDefinition defs) 
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

    Texture texture = Texture::LoadCubeMap(file_paths);
    m_textures.push_back(texture);

    return m_textures.back();
}



Texture& Renderer::LoadTexture(std::string path) {


    if(m_loadedTextureMap.find(path) != m_loadedTextureMap.end())
        return m_textures[m_loadedTextureMap[path]];

    
    auto texture = Texture::LoadTexture(path);

    m_textures.push_back(texture);
   
    m_loadedTextureMap[path] = m_textures.size() - 1;


    return m_textures.back();
}

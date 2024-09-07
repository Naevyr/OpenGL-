#include "ForwardPipeline.h"
#include "Light.h"
#include "Pipeline.h"
#include "Texture.h"
#include "TextureAllocator.h"
#include <stdexcept>



ForwardPipeline::ForwardPipeline(std::shared_ptr<TextureAllocator> textureAllocator) 
                
{  

    

    glGenFramebuffers(1, &m_ShadowFB);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFB);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glGenFramebuffers(1, &m_ColorFB);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ColorFB);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    

    
    glGenBuffers(1, &m_LightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light::Uniform), nullptr, GL_DYNAMIC_DRAW);


    TextureAllocator::RuntimeTextureSpecification shadowMapSpecs;
    shadowMapSpecs.width = 256;
    shadowMapSpecs.height = 256;
    shadowMapSpecs.format = GL_DEPTH_COMPONENT;
    shadowMapSpecs.internal_format = GL_DEPTH_COMPONENT24;
    shadowMapSpecs.encoding = GL_FLOAT;
    shadowMapSpecs.type = GL_TEXTURE_2D_ARRAY;
    shadowMapSpecs.depth = 20;
    m_shadowMap = m_textureAllocator->createTexture(shadowMapSpecs); 

    

    m_shadowMaterial = Material("resources/shaders/shadow.vert", "resources/shaders/shadow.frag");
    
 
}


void ForwardPipeline::render(RenderSpecifications& specs) {


    Pipeline::renderShadowMap(specs.scene);

    glBindFramebuffer(GL_FRAMEBUFFER, m_ColorFB);

    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, specs.colorTexture.GetTextureID(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, specs.depthTexture.GetTextureID(), 0);

    
    glViewport(0, 0, specs.colorTexture.GetWidth(), specs.colorTexture.GetHeight());
    
    SetTransformUniform(specs.projection, specs.view);
    //SetLightUniform(specs.scene.GetLights(), specs.scene.GetEnvironment());


    PrimitiveGroup primitiveGroup = specs.scene.GetPrimitiveGroup();
    
    while (primitiveGroup.next_pass.has_value())
    {
        for(auto&& primitive : primitiveGroup.)
        {

        }
    }
}



void ForwardPipeline::SetTransformUniform(glm::mat4 projection, glm::mat4 view) {


    for(auto material : m_materials)
    {

        material.Bind();
        material.SetUniform<glm::mat4>("u_Projection", projection);
        material.SetUniform<glm::mat4>("u_View", view);
    }
    

}



void ForwardPipeline::SetLightUniform(std::vector<Light>& lights, Environment& environment) {


    for(int i = 0; i < m_materials.size(); i++)
    {   
        
        auto material = m_materials[i];

        if(!material.GetLightingFlag()) continue;
        
        material.Bind();
    
        LightUniform u_Lights;

        u_Lights.count = lights.size();

        for(int i = 0; i < lights.size(); i++)
        {
            u_Lights.lights[i] = lights[i];
        }

        glBindBuffer(GL_UNIFORM_BUFFER,m_LightUBO);

        GLuint bindingPoint = 3;
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_LightUBO);


        glBufferData(GL_UNIFORM_BUFFER, sizeof(LightUniform), &u_Lights, GL_DYNAMIC_DRAW);
            
        material.BindBlock("u_Lights", bindingPoint);
        material.SetUniform<glm::vec4>("u_EnvironmentLighting", glm::vec4(environment.globalIllumination,environment.globalIlluminationIntensity));
    }


}
/*

unsigned int ForwardPipeline::LoadMaterial(MaterialDescription materialDefinition, std::unordered_map<std::string, unsigned int>& local_textures, std::vector<Texture>& global_textures) {



    auto material = Material("resources/shaders/standard.vert", "resources/shaders/standard.frag");
    std::string albedoPath = materialDefinition.albedoPath;
    if(local_textures.find(albedoPath) == local_textures.end())
    {       
        LocalTextureSpecs<1> specs;
        specs.path = {albedoPath};
        specs.format = GL_RGB;
        Texture texture = Texture::createTexture(specs);

        global_textures.push_back(texture);
        local_textures[albedoPath] =  global_textures.size() - 1;
        material.SetUniform<Texture&>("u_Albedo",global_textures[global_textures.size() - 1]);
    }
    else    
        material.SetUniform<Texture&>("u_Albedo", global_textures[local_textures[albedoPath]]);

    

    std::string normalPath = materialDefinition.normalPath;

    if(local_textures.find(normalPath) == local_textures.end())
    {   
        LocalTextureSpecs<1> specs;
        specs.path = {normalPath};
        specs.format = GL_RGB;
        Texture texture = Texture::createTexture(specs);
        global_textures.push_back(texture);
        local_textures[normalPath] =  global_textures.size() - 1;
        material.SetUniform<Texture&>("u_Normal",global_textures[global_textures.size() - 1]);
    }
    else
        material.SetUniform<Texture&>("u_Normal", global_textures[local_textures[normalPath]]);
     

    material.SetLightingFlag(materialDefinition.lightingEnabled);
    if(materialDefinition.lightingEnabled)
    {

        material.SetUniform<Texture&>("u_ShadowMap", m_shadowMap);
    }


    m_materials.push_back(material);
    return m_materials.size() - 1;
}

*/



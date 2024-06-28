#include "ForwardPipeline.h"



void ForwardPipeline::Initialize() {
    glGenFramebuffers(1, &m_ShadowFB);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFB);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    
    glGenBuffers(1, &m_LightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_LightUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightUniform), nullptr, GL_DYNAMIC_DRAW);



    glGenTextures(1, &m_ShadowMap);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_ShadowMap);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, 256, 256, 1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    m_shadowMaterial = Material("resources/shaders/shadow.vert", "resources/shaders/shadow.frag");
    
 
}


void ForwardPipeline::Render(Scene& scene, RenderSpecifications& specs) {

    RenderShadowMap(scene);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, specs.width, specs.height);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    SetTransformUniform(specs.projection, specs.view);
    SetLightUniform(scene.GetLights(), scene.GetEnvironment());


    for(auto mesh : scene.GetMeshes())

    {
        auto material = m_materials[mesh.getMaterialIndex()];
        material.Use();
        mesh.Draw(material);
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

        GLuint bindingPoint = 3; // Binding point index, adjust as needed
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_LightUBO);


        glBufferData(GL_UNIFORM_BUFFER, sizeof(LightUniform), &u_Lights, GL_DYNAMIC_DRAW);
            
        material.BindBlock("u_Lights", bindingPoint);
        material.SetUniform<glm::vec4>("u_EnvironmentLighting", glm::vec4(environment.globalIllumination,environment.globalIlluminationIntensity));
    }


}


unsigned int ForwardPipeline::LoadMaterial(MaterialDefinition materialDefinition, std::unordered_map<std::string, unsigned int>& local_textures, std::vector<Texture>& global_textures) {



    auto material = Material("resources/shaders/standard.vert", "resources/shaders/standard.frag");
    std::string albedoPath = materialDefinition.albedoPath;
    if(local_textures.find(albedoPath) == local_textures.end())
    {   
        Texture texture = Texture::LoadTexture(albedoPath);
        global_textures.push_back(texture);
        local_textures[albedoPath] =  global_textures.size() - 1;
        material.SetTexture("u_Albedo",global_textures[global_textures.size() - 1]);
    }
    else    
        material.SetTexture("u_Albedo", global_textures[local_textures[albedoPath]]);

    

    std::string normalPath = materialDefinition.normalPath;

    if(local_textures.find(normalPath) == local_textures.end())
    {   
        Texture texture = Texture::LoadTexture(normalPath);
        global_textures.push_back(texture);
        local_textures[normalPath] =  global_textures.size() - 1;
        material.SetTexture("u_Normal",global_textures[global_textures.size() - 1]);
    }
    else
        material.SetTexture("u_Normal", global_textures[local_textures[normalPath]]);
     

    material.SetLightingFlag(materialDefinition.lightingEnabled);
    if(materialDefinition.lightingEnabled)
    {
        if(m_shadowMapTextureIndex == -1)
        {
            global_textures.push_back(Texture::CreateTexture(m_ShadowMap,GL_TEXTURE_2D_ARRAY));
            m_shadowMapTextureIndex = global_textures.size() - 1;
        }
        material.SetTexture("u_ShadowMap", global_textures[m_shadowMapTextureIndex]);
    }


    m_materials.push_back(material);
    return m_materials.size() - 1;
}


void ForwardPipeline::RenderShadowMap(Scene& scene) {
 
    std::vector<Light>& lights = scene.GetLights();
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFB);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 256, 256);

    glBindTexture(GL_TEXTURE_2D_ARRAY, m_ShadowMap);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT24, 256, 256, lights.size(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    for (size_t i = 0; i < lights.size(); i++)
    {   
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowMap, 0, i);

        glClear(GL_DEPTH_BUFFER_BIT);




        glm::mat4 lightProjectionMatrix;

        switch (scene.GetLights()[i].type)
        {   
            case LightType::DIRECTIONAL:
                lightProjectionMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 100.0f);
                break;
            case LightType::POINT:
                lightProjectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 50.0f);
                 
                break;
           
            default:
                break;
        }

        glm::vec3 direction = lights[i].direction;
        glm::mat4 lightViewMatrix = glm::lookAt(lights[i].position, lights[i].position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
        lightViewMatrix[1][1] *= -1;


        glm::mat4 lightSpaceMatrix =   lightProjectionMatrix *  lightViewMatrix;   
        
        scene.GetLights()[i].lightSpaceMatrix = lightSpaceMatrix;
        m_shadowMaterial.Use();
        m_shadowMaterial.SetUniform<glm::mat4>("u_LightSpace", lightSpaceMatrix);


        
        for(auto mesh : scene.GetMeshes())
        {   
            mesh.Draw(m_shadowMaterial);
        }
    }

};



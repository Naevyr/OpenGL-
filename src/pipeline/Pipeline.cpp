
#include "pipeline/Pipeline.h"

void Pipeline::renderShadowMap(Scene& scene) {
 
    std::vector<Light>& lights = scene.GetLights();
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFB);
    m_shadowMap.Bind();
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT24, 256, 256, lights.size(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);


    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 256, 256);

    for (size_t i = 0; i < lights.size(); i++)
    {   
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMap.GetTextureID(), 0, i);
        glClear(GL_DEPTH_BUFFER_BIT);





        glm::mat4 lightProjectionMatrix;

        switch (scene.GetLights()[i].type)
        {   
            case LightType::DIRECTIONAL:
                lightProjectionMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 100.0f);
                break;
            case LightType::SPOT:
                lightProjectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
                 
                break;
            case LightType::POINT:
                throw  std::runtime_error("Point light not supported");
            default:
                break;
        }

        glm::vec3 direction = lights[i].direction;
        glm::mat4 lightViewMatrix = glm::lookAt(lights[i].position, lights[i].position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
        lightViewMatrix[1][1] *= -1;


        glm::mat4 lightSpaceMatrix =   lightProjectionMatrix *  lightViewMatrix;   
        
        scene.GetLights()[i].lightSpaceMatrix = lightSpaceMatrix;
        m_shadowMaterial.Bind();
        m_shadowMaterial.SetUniform<glm::mat4>("u_LightSpace", lightSpaceMatrix);


        
        for(auto mesh : scene.GetMeshes())
        {   
            mesh.Draw(m_shadowMaterial);
        }
    }

};

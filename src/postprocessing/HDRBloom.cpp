#include "HDRBloom.h"
#include "Texture.h"
#include "TextureAllocator.h"
#include <algorithm>
#include <memory>



HDRBloom::HDRBloom(std::shared_ptr<TextureAllocator> textureAllocator) {

    m_textureAllocator = textureAllocator;

    m_brightPass = SinglePassPostProcessingEffect<ComputeShader>("resources/shaders/bloom/brightPass.glsl");
    m_blur = ComputeShader("resources/shaders/compute/blur.glsl");
    m_downSample = ComputeShader("resources/shaders/compute/downsample.glsl");
    m_upSample = ComputeShader("resources/shaders/bloom/upSamplePass.glsl");
    m_add = ComputeShader("resources/shaders/compute/add.glsl");


    TextureAllocator::RuntimeTextureSpecification workTextureSpecs;
    workTextureSpecs.width = 800;
    workTextureSpecs.height = 600;
    workTextureSpecs.format = GL_RGBA;
    workTextureSpecs.internal_format = GL_RGBA32F;
    workTextureSpecs.mipmap_levels = 6;
    m_workTexture = m_textureAllocator->createTexture(workTextureSpecs);


    TextureAllocator::RuntimeTextureSpecification temporarySpecs;
    temporarySpecs.width = 800;
    temporarySpecs.height = 600;
    temporarySpecs.format = GL_RGBA;
    temporarySpecs.internal_format = GL_RGBA32F;
    temporarySpecs.mipmap_levels = 6;
    m_temporary = m_textureAllocator->createTexture(temporarySpecs);

}


void HDRBloom::run(Texture& input, Texture& output) {


    Texture& temporary = m_textureAllocator->getTexture(m_temporary);
    Texture& workTexture = m_textureAllocator->getTexture(m_workTexture);


    m_brightPass.run(input, temporary);

    m_blur.SetUniform("u_input", temporary);
    m_blur.SetTexture("u_output", workTexture, 0, GL_WRITE_ONLY);
    m_blur.SetUniform("u_blurSize", 4);
    m_blur.Dispatch({workTexture.getWidth(), workTexture.getHeight() , 1});
    

    for (size_t i = 1; i <= 6; i++)
    {

        
        m_downSample.SetTexture("u_input", workTexture, i - 1, GL_READ_ONLY);
        m_downSample.SetTexture("u_output", temporary, i, GL_WRITE_ONLY);
        m_downSample.Dispatch({workTexture.getWidth() /  pow(2,i), workTexture.getHeight() /  pow(2,i), 1});

        m_blur.SetTexture("u_input", temporary, i, GL_READ_ONLY);
        m_blur.SetTexture("u_output", workTexture, i, GL_WRITE_ONLY);
        m_blur.SetUniform("u_blurSize", 4);
        
        m_blur.Dispatch({workTexture.getWidth() /  pow(2,i), workTexture.getHeight() /  pow(2,i), 1});
        

        
    }
    
    for(int i = 5; i >= 0; i--)
    {
        m_upSample.SetTexture("u_input", workTexture, i + 1, GL_READ_ONLY);
        m_upSample.SetTexture("u_output", temporary, i, GL_WRITE_ONLY);
        if(i == -1)
            m_upSample.SetTexture("u_intermediate", input, 0, GL_READ_ONLY);
        else
            m_upSample.SetTexture("u_intermediate", workTexture, i, GL_READ_ONLY);

    
        m_upSample.Dispatch({workTexture.getWidth() / pow(2, i + 1), workTexture.getHeight() / pow(2, i + 1), 1});

        glCopyImageSubData(temporary.getID(), GL_TEXTURE_2D, i , 0, 0, 0,
                workTexture.getID(), GL_TEXTURE_2D,  i, 0, 0, 0,
                workTexture.getWidth() / pow(2, i ) , workTexture.getHeight() / pow(2, i ), 1);

    }


    m_add.SetTexture("u_input", workTexture, 0, GL_READ_ONLY);
    m_add.SetTexture("u_output", input, 0, GL_READ_ONLY);
    m_add.SetTexture("u_intermediate", output, 0, GL_WRITE_ONLY);
    m_add.Dispatch({input.getWidth(), input.getHeight(), 1});


}

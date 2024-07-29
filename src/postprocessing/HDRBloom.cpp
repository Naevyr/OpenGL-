#include "HDRBloom.h"
#include <algorithm>



void HDRBloom::Initialize()  {

    m_brightPass.Initialize("resources/shaders/bloom/brightPass.glsl");
    m_blur = ComputeShader("resources/shaders/compute/blur.glsl");
    m_downSample = ComputeShader("resources/shaders/compute/downsample.glsl");
    m_upSample = ComputeShader("resources/shaders/bloom/upSamplePass.glsl");
    m_add = ComputeShader("resources/shaders/compute/add.glsl");


    RuntimeTextureSpecs workTextureSpecs;
    workTextureSpecs.width = 800;
    workTextureSpecs.height = 600;
    workTextureSpecs.format = GL_RGBA;
    workTextureSpecs.internal_format = GL_RGBA32F;
    workTextureSpecs.mipmap_levels = 6;
    m_workTexture = Texture::CreateTexture(workTextureSpecs);


    RuntimeTextureSpecs temporarySpecs;
    temporarySpecs.width = 800;
    temporarySpecs.height = 600;
    temporarySpecs.format = GL_RGBA;
    temporarySpecs.internal_format = GL_RGBA32F;
    temporarySpecs.mipmap_levels = 6;
    m_temporary = Texture::CreateTexture(temporarySpecs);

}


void HDRBloom::Run(Texture& input, Texture& output) {



    m_brightPass.Run(input, m_temporary);

    m_blur.SetTexture(0, m_temporary, 0, GL_READ_ONLY);
    m_blur.SetTexture(1, m_workTexture, 0, GL_WRITE_ONLY);
    m_blur.SetUniform("u_blurSize", 10);
    m_blur.Dispatch({m_workTexture.GetWidth(), m_workTexture.GetHeight() , 1});
    

    for (size_t i = 1; i <= 6; i++)
    {

        
        m_downSample.SetTexture(0, m_workTexture, i - 1, GL_READ_ONLY);
        m_downSample.SetTexture(1, m_temporary, i, GL_WRITE_ONLY);
        m_downSample.Dispatch({m_workTexture.GetWidth() /  pow(2,i), m_workTexture.GetHeight() /  pow(2,i), 1});

        m_blur.SetTexture(0, m_temporary, i, GL_READ_ONLY);
        m_blur.SetTexture(1, m_workTexture, i, GL_WRITE_ONLY);
        m_blur.SetUniform("u_blurSize", 30);
        
        m_blur.Dispatch({m_workTexture.GetWidth() /  pow(2,i), m_workTexture.GetHeight() /  pow(2,i), 1});
        

        
    }
    
    for(int i = 5; i >= 0; i--)
    {
        m_upSample.SetTexture(0, m_workTexture, i + 1, GL_READ_ONLY);
        m_upSample.SetTexture(1, m_temporary, i, GL_WRITE_ONLY);
        if(i == -1)
            m_upSample.SetTexture(2, input, 0, GL_READ_ONLY);
        else
            m_upSample.SetTexture(2, m_workTexture, i, GL_READ_ONLY);

    
        m_upSample.Dispatch({m_workTexture.GetWidth() / pow(2, i + 1), m_workTexture.GetHeight() / pow(2, i + 1), 1});

        glCopyImageSubData(m_temporary.GetTextureID(), GL_TEXTURE_2D, i , 0, 0, 0,
                m_workTexture.GetTextureID(), GL_TEXTURE_2D,  i, 0, 0, 0,
                m_workTexture.GetWidth() / pow(2, i ) , m_workTexture.GetHeight() / pow(2, i ), 1);

    }


    m_add.SetTexture(0, m_workTexture, 0, GL_READ_ONLY);
    m_add.SetTexture(1, input, 0, GL_READ_ONLY);
    m_add.SetTexture(2, output, 0, GL_WRITE_ONLY);
    m_add.Dispatch({input.GetWidth(), input.GetHeight(), 1});


}

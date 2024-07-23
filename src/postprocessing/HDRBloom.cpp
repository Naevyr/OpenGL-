#include "HDRBloom.h"

void HDRBloom::Run(Texture& input, Texture& output) {


    m_brightPass.Run(input, m_brightPassOutput);
    m_downSample.Run(m_brightPassOutput, m_upsampledOutput);
    m_upSample.Run(m, m_brightPassOutput);




    m_brightPass.Run(m_upsampledOutput, output);
}
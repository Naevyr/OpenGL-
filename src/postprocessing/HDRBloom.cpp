#include "HDRBloom.h"

void HDRBloom::Run(Texture& input, Texture& output) {



    m_brightPass.Run(input, m_brightPassOutput);


    

}

void HDRBloom::Initialize()  {

}
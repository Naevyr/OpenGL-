#pragma once
#include "ComputeShader.h"

template <typename T>
class PostProcessingEffect{
    static_assert(std::is_base_of<Program, T>::value, "Post Effect must derive from a program")
    
    T m_program;

    public:

        virtual void Run(Texture& input, Texture& output);
};

template <>
class PostProcessingEffect<ComputeShader> {

    public:

        virtual void Run(Texture& input, Texture& output);
};
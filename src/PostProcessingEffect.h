#pragma once



class PostProcessingEffect {

   
    public:
        
        virtual void Initialize(std::string shaderPath) = 0;
        virtual void Run(Texture& input, Texture& output) = 0;
};


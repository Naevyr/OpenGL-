#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
class Program {
   
        
    public:
        static unsigned int Create(const char * vertexPath, const char * fragmentPath);
        static void Delete(unsigned int programID);

};
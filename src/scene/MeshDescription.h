#pragma once
#include <string>
#include "MaterialDescription.h"



struct MeshDescription {
    enum Type {
        STATIC,
        DYNAMIC
    };



    std::string filePath;
    MaterialDescription material;

};
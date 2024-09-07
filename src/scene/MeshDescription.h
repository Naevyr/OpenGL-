#pragma once
#include <string>
#include "MaterialDescription.h"
#include <optional>


struct MeshDescription {

    std::string filePath;
    std::optional<MaterialDescription> material;

};
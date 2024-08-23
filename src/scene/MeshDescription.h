#pragma once
#include <string>
#include "MaterialDescription.h"
#include <optional>


struct StaticMeshDescription {

    std::string filePath;
    std::optional<MaterialDescription> material;

};
#pragma once
#include <optional>
#include <string>

#include "MaterialDescription.h"

struct MeshDescription {
	std::string filePath;
	std::optional<MaterialDescription> material;
};
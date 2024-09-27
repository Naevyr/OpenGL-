#pragma once

#include <optional>

#include "Node.h"
#include "Primitive.h"
#include "ResourceTypes.h"

struct RenderPassSpecs {
	std::optional<MaterialHandle> materialOverride;

	std::vector<TextureHandle> renderTargets;
	std::vector<TextureHandle> renderInputs;

	std::vector<std::reference_wrapper<Primitive>> primitives;
};
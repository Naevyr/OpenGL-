#pragma once

#include "Node.h"
#include "ResourceTypes.h"

struct RenderPassSpecs {
	ProgramHandle program;
	std::vector<TextureHandle> renderTargets;
	std::vector<TextureHandle> renderInputs;
	std::vector<NodeID> primitives;
};
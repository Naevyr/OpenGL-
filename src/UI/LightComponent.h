#pragma once
#include "Light.h"

class LightComponent {
public:
	static void Render(Light& light, bool* keepOpen);
};
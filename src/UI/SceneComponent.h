#pragma once
#include <set>

#include "Scene.h"

class SceneComponent {
private:
	static std::set<int> m_displayedLights;
	static std::set<int> m_displayedMeshes;

public:
	static void Render(Scene& scene);
};
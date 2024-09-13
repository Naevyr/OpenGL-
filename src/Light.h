#pragma once
#include <glm/glm.hpp>

#include "Node.h"

class Light : public Node {
public:
	enum Type {
		POINT = 0,
		DIRECTIONAL = 1,
		SPOT = 2
	};
	struct Uniform;

private:
	friend class LightComponent;
	glm::vec3 m_color;
	float m_intensity;
	Type m_type;

public:
	Light();

	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setIntensity(float intensity);
	float getIntensity();
	void setType(Type type);
	Type getType();

	Light::Uniform getUniformStruct();
};

struct Light::Uniform {
	glm::mat4 lightSpaceMatrix;
	glm::vec3 position;
	float _padding1;
	glm::vec3 color;
	float _padding2;
	glm::vec3 direction;
	float intensity;

	Light::Type type;

	int _padding3[3];
};
struct LightUniformBuffer {
	unsigned int count;
	int padding[3];
	Light lights[20];
};
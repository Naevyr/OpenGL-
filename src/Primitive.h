#pragma once
#include "Material.h"
#include "Node.h"
#include "VertexArray.h"

class Primitive : public Node {
private:
	VertexArray m_vertexArray;
	MaterialHandle m_material;

public:
	Primitive(VertexArray vertexArray, unsigned int materialIndex);
	inline MaterialHandle getMaterialIndex() { return m_material; }
};
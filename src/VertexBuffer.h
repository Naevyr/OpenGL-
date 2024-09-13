#pragma once

#include <map>
#include <vector>

class VertexBuffer {
private:
	unsigned int m_glID;
	unsigned int m_instancedMeshes;
	bool m_isStatic;

	struct DataOffset {
		unsigned int offset;
		unsigned int size;
	};
	std::map<unsigned int, DataOffset> m_offsets;

public:
	VertexBuffer();
	void Bind() const;

	unsigned int addMesh(std::vector<unsigned char>& data);
	void removeMesh(unsigned int m_meshID);

	void setUsage(bool staticBuffer);
	inline bool isStatic() const { return m_isStatic; }

	~VertexBuffer();
};

#pragma once

#include <vector>
#include "../../Math/Vertex.h"

class VertexBuffer {

public:
	VertexBuffer(const std::vector<Vertex>& Vertices, unsigned int Size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int RendererId;
};
#pragma once
#include "System.h"
#include "../../../Math/Vertex.h"

#include <vector>

struct CubeMesh {
	static const std::vector<Vertex> Vertices;
	static const std::vector<unsigned int> Indices;
};

class RenderSystem : public System
{

public:
	RenderSystem();

	virtual void Tick(const float deltaTime);

	bool isDirty = true;
};


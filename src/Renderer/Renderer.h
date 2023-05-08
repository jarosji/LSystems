#pragma once

class VertexArray;
class IndexBuffer;

class Renderer
{
public:
	static void Clear();
	static void Draw(const VertexArray& Va, const IndexBuffer& Ib);
};


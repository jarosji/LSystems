#include "VertexBuffer.h"

#include <glad/gl.h>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& Vertices, unsigned int Size)
{
	//Vertex buffer
	glGenBuffers(1, &RendererId);
	glBindBuffer(GL_ARRAY_BUFFER, RendererId);
	glBufferData(GL_ARRAY_BUFFER, Size, Vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &RendererId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, RendererId);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#include "IndexBuffer.h"

#include <glad/gl.h>

IndexBuffer::IndexBuffer(std::vector<unsigned int> Indices, unsigned int Count)
	:Count(Count)
{
	//Index buffer
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	: id(other.id), Count(other.Count)
{
	other.id = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
	if (id) glDeleteBuffers(1, &id);

	id = other.id;
	Count = other.Count;

	other.id = 0;
	return *this;
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

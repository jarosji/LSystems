#include "VertexArray.h"
#include"VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
	:type(GL_TRIANGLES)
{
	//VAO
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: id(other.id), type(other.type)
{
	other.id = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (id) glDeleteVertexArrays(1, &id);

	id = other.id;
	type = other.type;

	other.id = 0;
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	//Attrib
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.Count, element.Type, element.bIsNormalized, layout.GetStride(), (const void*)offset);
		offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

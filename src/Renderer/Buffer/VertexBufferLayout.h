#pragma once

#include <vector>
#include <glad/gl.h>

struct VertexBufferElement {
	unsigned int Type;
	unsigned int Count;
	unsigned int bIsNormalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout {

public:
	VertexBufferLayout()
		: Stride(0)
	{}

	//On my other PC static_assert isn't working :(
	template<typename T>
	void Push(unsigned int count) {
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned int GetStride() const { return Stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return Elements; }

private:
	std::vector<VertexBufferElement> Elements;
	unsigned int Stride;
};
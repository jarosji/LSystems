#pragma once

#include <vector>

class IndexBuffer {

public:
	IndexBuffer(std::vector<unsigned int> Indices, unsigned int Count);
	~IndexBuffer();

	// Non copyable
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	// move constructor
	IndexBuffer(IndexBuffer&& other) noexcept;
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return Count; }

private:
	unsigned int id;
	unsigned int Count;
};
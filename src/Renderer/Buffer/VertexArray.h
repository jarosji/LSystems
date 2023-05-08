#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	// non copyable
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete; 

	// movable
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

	void SetType(int inType) { type = inType; }
	int GetType() const { return type; }


private:
	unsigned int id;
	int type;
};
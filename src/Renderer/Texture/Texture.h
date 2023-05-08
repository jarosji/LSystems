#pragma once

#include <string>

class Texture {
public:

	Texture();
	Texture(const std::string& filepath);
	~Texture();

	// non copyable
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete; 

	// move constructor
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetBPS() const { return bpp; }

private:
	unsigned int id;
	std::string filepath;
	unsigned char* localBuffer;
	int width, height, bpp;
};
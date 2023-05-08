#include "Texture.h"

#include "../../External/stb/stb_image.h"
#include <glad/gl.h>

Texture::Texture()
	: id(0), filepath(""), localBuffer(nullptr), width(0), height(0), bpp(0)
{
}

Texture::Texture(const std::string& filepath)
	:filepath(filepath), localBuffer(nullptr), width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(true);
	localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}

	stbi_set_flip_vertically_on_load(false);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

Texture::Texture(Texture&& other) noexcept
	: id(other.id), filepath(std::move(other.filepath)), localBuffer(other.localBuffer),
	width(other.width), height(other.height), bpp(other.bpp)
{
	// wipe program_ so the destructor doesn't release it...
	other.id = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (id) glDeleteTextures(1, &id);
	id = other.id;
	filepath = std::move(other.filepath);
	localBuffer = other.localBuffer;
	width = other.width;
	height = other.height;
	bpp = other.bpp;

	other.id = 0;
	return *this;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

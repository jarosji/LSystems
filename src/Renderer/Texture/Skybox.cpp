#include "Skybox.h"
#include "../../External/stb/stb_image.h"

#include <glad/gl.h>
#include <iostream>

Skybox::Skybox()
	: id(0), localBuffer(NULL), width(0), height(0), nrChannels(0)
{
}

Skybox::Skybox(const std::string filepath[6])
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	for (unsigned int i = 0; i < 6; i++) {
	
		localBuffer = stbi_load(filepath[i].c_str(), &width, &height, &nrChannels, 0);
		if (localBuffer) {
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				localBuffer
			);
			stbi_image_free(localBuffer);
		}
		else {
			std::cout << "Failed load tex Sky" << std::endl;
			stbi_image_free(localBuffer);
		}
	}
}

void Skybox::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void Skybox::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

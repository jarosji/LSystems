#pragma once

#include <string>

class Skybox {
public:
	Skybox();
	Skybox(const std::string filepath[6]);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;

	unsigned char* localBuffer;
	int width, height, nrChannels;
};
#pragma once

#include "../Renderer/Shader/Shader.h"
#include "../Renderer/Texture/Texture.h"

#include <string>
#include <unordered_map>


class ShaderLibrary {

public:
	ShaderLibrary()
	{
		std::cout << "Shader library constructed" << std::endl;
	}

	std::unordered_map<std::string, Shader> shaders;
};

class TextureLibrary {

public:
	TextureLibrary()
	{
		std::cout << "Texture library constructed" << std::endl;
	}

	std::unordered_map<std::string, Texture> textures;
};

class SkyboxLibrary {

public:
	SkyboxLibrary()
	{
		std::cout << "Skybox library constructed" << std::endl;
	}

	std::unordered_map<std::string, Skybox> skyboxes;
};


namespace AssetLib {
	inline ShaderLibrary ShaderLib;
	inline TextureLibrary TextureLib;
	inline SkyboxLibrary SkyboxLib;
}
#pragma once

#include <string>

class Entity;

class ComponentPanel
{
public:
	void DrawGui();

private:
	void DrawTransform(Entity selectedEntity);
	void DrawLSystem(Entity selectedEntity);
	void DrawPointLight(Entity selectedEntity);
	void DrawSpotLight(Entity selectedEntity);
	void DrawDirectionalLight(Entity selectedEntity);

	std::string str0 = "";
	std::string str1 = "";
};


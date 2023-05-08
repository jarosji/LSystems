#pragma once

#include "../Scene/GUI/HierarchyPanel.h"
#include "../Scene/GUI/ComponentPanel.h"
#include "../Scene/Scene.h"

#include <imgui.h>

class ImGuiIO;
class Window;
class Event;

class Level
{
public:
	Level();

	virtual void Tick(const float delta);
	virtual void DrawGUI();
	void OnEvent(Event& e);

private:
	void SetupDocking();


	bool vsync = true;
	bool skybox = true;
	ImGuiIO* io;

	HierarchyPanel hierarchy;
	ComponentPanel component;
};


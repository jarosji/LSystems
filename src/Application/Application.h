#pragma once


#include "Window.h"
#include "../Scene/Scene.h"
#include "../Level/Level.h"

#include <memory>

//Only works for async generatio of LSystems
#define ASYNC 0;


class Application
{
public:
	Application();

	void Run();

	void Tick(const float delta);
	void Render();

	template<typename LevelType>
	void SwitchLevel() {
		World::scene.Clear();
		EntityReg::registry.Clear();
		World::scene.lSystem.Clear();
		currentLevel = std::make_unique<LevelType>();
	}

	void OnEvent(Event& e);

	Window& GetWindow() { return window; }
	static Application* GetApplication() { return appInstance; }

private:
	static Application* appInstance;

	Window window;
	std::unique_ptr<Level> currentLevel;
};


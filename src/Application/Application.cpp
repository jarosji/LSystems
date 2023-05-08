#include "Application.h"

#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.h"
#include "../Debug/Debug.h"
#include "../Scene/Scene.h"
#include "../Level/LSystemLevel/LSystemLevel.h"
#include "../Level/Playground/PlaygroundLevel.h"

#include <time.h>
#include <memory>
#include <iostream>
#include "../Level/EmptyLevel/EmptyLevel.h"

Application* Application::appInstance = nullptr;

Application::Application() : window(1400, 800)
{
	appInstance = this;

	if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD.\n" << std::endl;
	}

	Debug::RegisterOpenGLDebug();

	window.RegisterEvent(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	World::scene.systems.push_back(std::make_shared<RenderSystem>());

	currentLevel = std::make_unique<LSystemLevel>();
}

void Application::Run()
{
	float lastTick = clock();
	float delta = 0;

	while (!window.GetWindowShouldClose()) {
		delta = (clock() - lastTick);
		lastTick = clock();

		Tick(delta);
		Render();
	}
}

void Application::Tick(const float delta)
{

	//Maybe scene should Tick in future?
	currentLevel->Tick(delta);
	World::scene.lSystem.Tick(delta);
	World::scene.camera.Tick(delta);
}

void Application::Render()
{
	Renderer::Clear();

	//This shouldn't be here - create better handling for systems
	for (std::shared_ptr<System> system : World::scene.systems) {
		system->Tick(0);
	}	

	window.StartFrame();
	currentLevel->DrawGUI();
	window.EndFrame();
}

void Application::OnEvent(Event& e)
{
	currentLevel->OnEvent(e);
}
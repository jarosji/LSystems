#include "Level.h"
#include "../Events/Event.h"
#include "../Application/Application.h"
#include "Playground/PlaygroundLevel.h"
#include "LSystemLevel/LSystemLevel.h"
#include "EmptyLevel/EmptyLevel.h"

#include <GLFW/glfw3.h>


Level::Level()
{
	io = &ImGui::GetIO();

	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	World::scene.camera.SetProjMat(ViewType::PERSPECTIVE, Application::GetApplication()->GetWindow().GetWidth(),
		Application::GetApplication()->GetWindow().GetHeight());

	//World::scene.camera.SetPosition(glm::vec3(0, 2, 5));

	//SKYBOX
	{
		std::string skyboxPath[6] = {
			"res/textures/skyboxes/right.jpg",
			"res/textures/skyboxes/left.jpg",
			"res/textures/skyboxes/top.jpg",
			"res/textures/skyboxes/bottom.jpg",
			"res/textures/skyboxes/front.jpg",
			"res/textures/skyboxes/back.jpg"
		};

		AssetLib::SkyboxLib.skyboxes.emplace("Islands", skyboxPath);
	}

	AssetLib::ShaderLib.shaders.emplace("Basic", "res/shaders/Basic.shader");
	AssetLib::ShaderLib.shaders.emplace("Skybox", "res/shaders/Skybox.shader");
	AssetLib::ShaderLib.shaders.emplace("Light", "res/shaders/Light.shader");

	AssetLib::TextureLib.textures.emplace("container", "res/textures/container.png");
	AssetLib::TextureLib.textures.emplace("container_specular", "res/textures/container_specular.png");
	AssetLib::TextureLib.textures.emplace("magic", "res/textures/magic.jpeg");
	AssetLib::TextureLib.textures.emplace("black", "res/textures/black.jpg");
}

void Level::Tick(const float delta)
{
}

void Level::DrawGUI()
{
	SetupDocking();

	ImGui::Begin("Levels");

		if (ImGui::Button("Empty Level")) {
			Application::GetApplication()->SwitchLevel<EmptyLevel>();
		}
		if (ImGui::Button("LSystem Level")) {
			Application::GetApplication()->SwitchLevel<LSystemLevel>();
		}
		if (ImGui::Button("Playground Level")) {
			Application::GetApplication()->SwitchLevel<PlaygroundLevel>();
		}

	hierarchy.DrawGui();
	component.DrawGui();

	ImGui::End();
}

void Level::OnEvent(Event& e)
{
	if (WindowResizeEvent* ev = dynamic_cast<WindowResizeEvent*>(&e)) {

		if (ev->GetWidth() == 0 || ev->GetHeight() == 0)
		{
			//Minimization
			return;
		}
		glViewport(0, 0, ev->GetWidth(), ev->GetHeight());
		World::scene.camera.SetProjMat(ViewType::PERSPECTIVE, ev->GetWidth(), ev->GetHeight());
	}

	else if (KeyPressedEvent* ev = dynamic_cast<KeyPressedEvent*>(&e)) {
		if (World::scene.selectedEntity.GetId() != null_entity && ev->GetKeyCode() == GLFW_KEY_DELETE) {
			World::scene.DeleteEntity(World::scene.selectedEntity);
			World::scene.selectedEntity = null_entity;
		}
	}

	else if (ScrollEvent* ev = dynamic_cast<ScrollEvent*>(&e)) {
		World::scene.camera.AdjustSpeed(ev->GetOffsetY());
	}
}

void Level::SetupDocking()
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	if (dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	bool open = true;
	ImGui::Begin("DockSpace Demo", &open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();

	ImGui::Begin("Settings");

	if (ImGui::Checkbox("Vsync", &vsync)) {
		Application::GetApplication()->GetWindow().EnableVSync(vsync);
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

	ImGui::End();
}

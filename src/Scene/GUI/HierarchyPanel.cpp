#include "HierarchyPanel.h"

#include <imgui.h>

#include "../ECS/Entity.h"
#include "../Scene.h"

void HierarchyPanel::DrawGui()
{
	ImGui::Begin("Entities");

	ImGui::LabelText("##Spawn", "Spawner: ");

	if (ImGui::Button("Cube", ImVec2(120, 20))) {
		Entity ent = World::scene.CreateEntity("Cube");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<MaterialColorComponent>(glm::vec4(1, 0, 0, 1));
	}

	ImGui::SameLine();

	if (ImGui::Button("Textured Cube", ImVec2(120, 20))) {
		Entity ent = World::scene.CreateEntity("Cube");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["container"],
			&AssetLib::TextureLib.textures["container_specular"],
			32);
	}

	if (ImGui::Button("LSystem", ImVec2(120, 20))) {
		Entity ent = World::scene.CreateEntity("LSystem");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<LSystemComponent>();
		ent.AddComponent<MaterialColorComponent>(glm::vec4(0, 1, 0, 1));
	}

	ImGui::SameLine();
	if (ImGui::Button("Textured LSystem", ImVec2(120, 20))) {
		Entity ent = World::scene.CreateEntity("LSystem");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<LSystemComponent>();
		auto& a = ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["black"],
			&AssetLib::TextureLib.textures["black"],
			32);
		a.Color = glm::vec4(1, 0, 0, 1);
	}

	if (ImGui::Button("Skybox", ImVec2(120, 20))) {
		Entity ent = World::scene.CreateEntity("Skybox");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<SkyboxComponent>(AssetLib::SkyboxLib.skyboxes["Islands"]);
	}

	if (ImGui::BeginListBox("##actorBox", ImVec2(300, 200)))
	{
		for (auto& [key, value] : World::scene.GetEntities())
		{
			auto& descriptor = value.GetComponent<EntityDescriptorComponent>();
			const std::string& s = "[" + std::to_string(descriptor.Id) + "] " + descriptor.Name;

			const bool is_selected = (World::scene.selectedEntity.GetId() == descriptor.Id);
			if (ImGui::Selectable(s.c_str(), is_selected)) {
				World::scene.selectedEntity = descriptor.Id;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}
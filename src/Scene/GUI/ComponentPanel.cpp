#include "ComponentPanel.h"

#include "../Scene.h"
#include "../ECS/Entity.h"

#include <imgui.h>
#include <ImGUI/imgui_stdlib.h>

void ComponentPanel::DrawGui()
{
	Entity selectedEntity = World::scene.selectedEntity;
	if (!selectedEntity.IsValid())
		return;

	ImGui::Begin("Components");

	if (selectedEntity.HasComponent<TransformComponent>())
		DrawTransform(selectedEntity);

	if (selectedEntity.HasComponent<LSystemComponent>())
		DrawLSystem(selectedEntity);

	if (selectedEntity.HasComponent<PointLight>())
		DrawPointLight(selectedEntity);
	if (selectedEntity.HasComponent<SpotLight>())
		DrawSpotLight(selectedEntity);
	if (selectedEntity.HasComponent<DirectionalLight>())
		DrawDirectionalLight(selectedEntity);

	ImGui::End();
}

void ComponentPanel::DrawTransform(Entity selectedEntity)
{
	TransformComponent& transform = selectedEntity.GetComponent<TransformComponent>();

	glm::vec3 translation = transform.Position;
	glm::vec3 rotation = transform.Rotation;
	glm::vec3 scale = transform.Scale;

	if (ImGui::DragFloat3("translation", &translation.x, 0.1f)) {
		transform.Position = translation;
		transform.dirty = true;
	}
	if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f)) {
		transform.Rotation = rotation;
		transform.dirty = true;
	}
	if (ImGui::DragFloat3("Scale", &scale.x, 0.1f)) {
		transform.Scale = scale;
		transform.dirty = true;
	}
}

void ComponentPanel::DrawLSystem(Entity selectedEntity)
{
	ImGui::Separator();
	LSystemComponent& lSysComponent = selectedEntity.GetComponent<LSystemComponent>();

	if (ImGui::Button("Preset 1", ImVec2(75, 20))) {
		lSysComponent.SetPreset(Preset1::preset.angle, Preset1::preset.axiom, Preset1::preset.rules);
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}
	ImGui::SameLine();
	if (ImGui::Button("Preset 2", ImVec2(75, 20))) {
		lSysComponent.SetPreset(Preset2::preset.angle, Preset2::preset.axiom, Preset2::preset.rules);
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}

	if (ImGui::Button("Preset 3", ImVec2(75, 20))) {
		lSysComponent.SetPreset(Preset3::preset.angle, Preset3::preset.axiom, Preset3::preset.rules);
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}
	ImGui::SameLine();
	if (ImGui::Button("Preset 4", ImVec2(75, 20))) {
		lSysComponent.SetPreset(Preset4::preset.angle, Preset4::preset.axiom, Preset4::preset.rules);
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}

	static int item_current_idx = 0;
	if (ImGui::BeginListBox("Rules"))
	{
		for (int n = 0; n < lSysComponent.rules.size(); n++)
		{

			std::string id = "X##" + std::to_string(n);
			if (ImGui::Button(id.c_str(), ImVec2(20, 17.5f))) {
				lSysComponent.rules.erase(lSysComponent.rules.begin() + n);
				World::scene.lSystem.Update(selectedEntity, lSysComponent);
				continue;
			}
			ImGui::SameLine();
			const bool is_selected = (item_current_idx == n);
			std::string str = lSysComponent.rules[n].a + " -> " + lSysComponent.rules[n].b;
			if (ImGui::Selectable(str.c_str(), is_selected))
				item_current_idx = n;

			
			
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	//static char str0[128] = "";
	//static char str1[128] = "";
	ImGui::PushItemWidth(40);
	ImGui::InputText("##string", &str0);
	ImGui::SameLine();
	ImGui::PopItemWidth();

	ImGui::PushItemWidth(50);
	ImGui::LabelText("##MapsToLabel", "Map to:");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushItemWidth(70);
	ImGui::InputText("##MapsTo", &str1);
	ImGui::PopItemWidth();
	ImGui::SameLine();

	if (ImGui::Button("Upload Rule", ImVec2(50, 20))) {
		lSysComponent.rules.emplace_back(Rule{ str0 , str1 });
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
		str0 = "";
		str1 = "";
	}

	if (ImGui::InputText("Axiom", &lSysComponent.axiom)) {
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}

	if (ImGui::DragFloat("Angle", &lSysComponent.angle, 1, 0, 360)) {
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}

	if (ImGui::InputInt("Iterations", &lSysComponent.iteration, 1, 1)) {
		World::scene.lSystem.Update(selectedEntity, lSysComponent);
	}
}

void ComponentPanel::DrawPointLight(Entity selectedEntity)
{
	ImGui::Separator();
	PointLight& light = selectedEntity.GetComponent<PointLight>();

	ImGui::ColorEdit3("PointAmbient", &light.Ambient.x);
	ImGui::ColorEdit3("PointSpecular", &light.Specular.x);
	ImGui::ColorEdit3("PointDiffuse", &light.Diffuse.x);

	ImGui::DragFloat("PointConstant", &light.Constant, 0.001f, 0, 10, "%.4f");
	ImGui::DragFloat("PointLinear", &light.Linear, 0.001f, 0, 10, "%.4f");
	ImGui::DragFloat("PointQuadratic", &light.Quadratic, 0.001f, 0, 10, "%.4f");
}

void ComponentPanel::DrawSpotLight(Entity selectedEntity)
{
	ImGui::Separator();
	SpotLight& light = selectedEntity.GetComponent<SpotLight>();

	ImGui::ColorEdit3("SpotAmbient", &light.Ambient.x);
	ImGui::ColorEdit3("SpotSpecular", &light.Specular.x);
	ImGui::ColorEdit3("SpotDiffuse", &light.Diffuse.x);

	ImGui::DragFloat("SpotConstant", &light.Constant, 0.001f, 0, 10, "%.4f");
	ImGui::DragFloat("SpotLinear", &light.Linear, 0.001f, 0, 10, "%.4f");
	ImGui::DragFloat("SpotQuadratic", &light.Quadratic, 0.001f, 0, 10, "%.4f");

	ImGui::DragFloat("SpotCutOff", &light.CutOff, 0.001f, 0, 100, "%.4f");
	ImGui::DragFloat("SpotOuterCutOff", &light.OuterCutOff, 0.001f, 0, 100, "%.4f");
}

void ComponentPanel::DrawDirectionalLight(Entity selectedEntity)
{
	ImGui::Separator();
	DirectionalLight& light = selectedEntity.GetComponent<DirectionalLight>();

	ImGui::ColorEdit3("DirectionalAmbient", &light.Ambient.x);
	ImGui::ColorEdit3("DirectionalSpecular", &light.Specular.x);
	ImGui::ColorEdit3("DirectionalDiffuse", &light.Diffuse.x);
}

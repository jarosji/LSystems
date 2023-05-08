#include "LSystemLevel.h"
#include "../../Scene/Scene.h"
#include "../../Renderer/Shader/Shader.h"
#include "../../Scene/ECS/Systems/LSystem.h"
#include "../../Scene/ECS/Systems/RenderSystem.h"
#include "../../Application/Window.h"
#include "../../Scene/AssetLib.h"
#include "../../Application/Application.h"
#include "../../Math/Math.h"

#include <sstream>
#include <memory>

#include <ImGUI/imgui.h>
#include <GLFW/glfw3.h>



LSystemLevel::LSystemLevel()
{
	World::scene.camera.SetPosition(glm::vec3(0, 2, 10));
	World::scene.camera.SetRotation(glm::vec3(0, 0, 180));

	//Main entities
	{
		Entity ent = World::scene.CreateEntity("Floor");
		
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);

		auto& transform = ent.GetComponent<TransformComponent>();
		transform.Position = glm::vec3(0, 0, 0);
		transform.Scale = glm::vec3(100, 0.1f, 100);
		transform.dirty = true;

		auto& Mat = ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["black"],
			&AssetLib::TextureLib.textures["black"],
			32);
		Mat.Color = glm::vec4(1, 1, 1, 1);

		{
			Entity ent = World::scene.CreateEntity("CenterLight", glm::vec3(0, 0, 0));
			ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
			auto& light = ent.AddComponent<PointLight>();

			light.Index = 1;
			light.Ambient = glm::vec3(1, 1, 1);
			light.Diffuse = glm::vec3(1, 1, 1);
			light.Specular = glm::vec3(1, 1, 1);
			light.Linear = 0.0002f;
			light.Quadratic = 0.007f;

			auto& transform = ent.GetComponent<TransformComponent>();
			transform.Rotation = glm::vec3(90, 45, 0);
			transform.Scale = glm::vec3(1, 8, 1);
			transform.dirty = true;

			auto& material = ent.AddComponent<MaterialColorComponent>(glm::vec4(1, 1, 1, 1));

		}

		{
			Entity ent = World::scene.CreateEntity("DirectionalLight", glm::vec3(-1, 0, 0));
			auto& light = ent.AddComponent<DirectionalLight>();

			light.Diffuse = glm::vec3(0, 0, 0);

			auto& transform = ent.GetComponent<TransformComponent>();
			transform.Rotation = glm::vec3(360, 360, 360);
			transform.dirty = true;
		}
	}

	//Left
	{
		Entity ent = World::scene.CreateEntity("Spotlight", glm::vec3(-30, 50, 0));
		spotLight = &World::scene.GetEntityRef(ent.GetId());
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		auto& light = ent.AddComponent<SpotLight>();

		auto& tran = ent.GetComponent<TransformComponent>();
		tran.Rotation = glm::vec3(0, 360, 0);
		tran.dirty = true;


		light.Ambient = glm::vec3(0.84f, 0, 0.83f);
		light.Diffuse = glm::vec3(0.84f, 0, 0.83f);
		light.Specular = glm::vec3(1, 1, 1);
		light.Linear = 0.002f;
		light.Quadratic = 0.00f;
		light.Constant = 0.2f;

		ent.AddComponent<MaterialColorComponent>(glm::vec4(0.84f, 0, 0.83f, 1));

		{
			Entity ent = World::scene.CreateEntity("SpotLSystem", glm::vec3(-30, 0, 0));
			ent.AddComponent<MeshComponent>();
			ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
				&AssetLib::TextureLib.textures["container_specular"],
				32);

			auto& lsys = ent.AddComponent<LSystemComponent>();
			lsys.SetPreset(Preset1::preset.angle, Preset1::preset.axiom, Preset1::preset.rules);
			lsys.iteration = 11;
			World::scene.lSystem.Update(ent, lsys);
		}
	}

	//Mid
	 {
		Entity ent = World::scene.CreateEntity("TravelLight", glm::vec3(0, 2, -30));
		travelLight = &World::scene.GetEntityRef(ent.GetId());
		auto& light = ent.AddComponent<PointLight>();

		light.Index = 0;
		light.Ambient = glm::vec3(0, 0.67f, 0.86f);
		light.Specular = glm::vec3(0, 0, 0);
		light.Diffuse = glm::vec3(0, 1, 1);
		light.Constant = 0.596f;
		light.Linear = 0.001f;
		light.Quadratic = 0.002f;

		{
			Entity ent = World::scene.CreateEntity("Cube", glm::vec3(0, 0.5f, -30));
			ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
			ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
				&AssetLib::TextureLib.textures["container_specular"],
				32);
		}

		{
			Entity ent = World::scene.CreateEntity("2DL-System", glm::vec3(0, 0, -30));
			ent.AddComponent<MeshComponent>();
			ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
				&AssetLib::TextureLib.textures["container_specular"],
				32);

			auto& lsys = ent.AddComponent<LSystemComponent>();
			lsys.SetPreset(Preset4::preset.angle, Preset4::preset.axiom, Preset4::preset.rules);
			lsys.iteration = 5;
			World::scene.lSystem.Update(ent, lsys);
		}
	}

	 //Right
	{
		{
			Entity ent = World::scene.CreateEntity("DynamicLight", glm::vec3(30, 11, 10));
			pLight = &World::scene.GetEntityRef(ent.GetId());
			auto& light = ent.AddComponent<PointLight>();
			light.Index = 2;
			//ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);

			light.Ambient = glm::vec3(0, 0, 1);
			light.Specular = glm::vec3(0, 0, 0);
			light.Diffuse = glm::vec3(0.25f, 0.5f, 1);
			light.Constant = 0.3f;
			light.Linear = 0.0002f;
			light.Quadratic = 0.007f;
		}

		{
			Entity ent = World::scene.CreateEntity("Cube", glm::vec3(30, 0, 10));
			ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
			ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
				&AssetLib::TextureLib.textures["container_specular"],
				32);
		}

		{
			Entity ent = World::scene.CreateEntity("DynamicLSystem", glm::vec3(30, 0, 10));
			ent.AddComponent<MeshComponent>();
			ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
				&AssetLib::TextureLib.textures["container_specular"],
				32);

			auto& lsys = ent.AddComponent<LSystemComponent>();
			lsys.SetPreset(Preset1::preset.angle, Preset1::preset.axiom, Preset1::preset.rules);
			lsys.iteration = 11;
			World::scene.lSystem.Update(ent, lsys);
		}
	}
}

void LSystemLevel::Tick(const float delta)
{
	if (travelLight->IsValid()) {
		auto& transform = travelLight->GetComponent<TransformComponent>();
		transform.Position += glm::vec3(-0.02 * delta, 0.1 * delta, 0);

		if (transform.Position.y >= 150) {
			transform.Position = glm::vec3(2, 0, transform.Position.z);
		}
	}


	if (pLight->IsValid()) {
		auto& light = pLight->GetComponent<PointLight>();

		if (light.Linear <= 0.002f) accLinear = accLinearInit;
		if (light.Linear >= 0.10f) accLinear = -accLinearInit;

		if (light.Quadratic <= 0.00025f) accQuad = accQuadInit;
		if (light.Quadratic >= 0.05f) accQuad = -accQuadInit;

		light.Linear += accLinear * delta;
		light.Quadratic += accQuad * delta;
	}

	if (spotLight && spotLight->IsValid()) {
		auto& tran = spotLight->GetComponent<TransformComponent>();

		time += delta;
		//float val = glm::cos(time * 0.0025f) * 0.0015f * delta;
		float val = Math::SmoothStep(-200, 200, Math::PingPong(time * 0.0005, 1));

		tran.Rotation = glm::vec3(tran.Rotation.x, tran.Rotation.y, val);
		tran.dirty = true;
	}
}

void LSystemLevel::DrawGUI()
{
	Level::DrawGUI();
}

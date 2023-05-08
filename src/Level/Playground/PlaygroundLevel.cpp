#include "PlaygroundLevel.h"

#include <random>

PlaygroundLevel::PlaygroundLevel()
{
	//float x = -100;
	//float z = -100;
	//for (int i = 0; i < 30000; i++) {
	//	Entity ent = EntityReg::registry.CreateEntity("Hello entity");
	//	ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
	//	ent.AddComponent<MaterialTextureComponent>(&AssetLib::TextureLib.textures["magic"],
	//		&AssetLib::TextureLib.textures["container_specular"],
	//		32);
	//	
	//	auto& transform = ent.GetComponent<TransformComponent>();
	//	transform.Position = glm::vec3(x, 0, z);
	//	transform.dirty = true;

	//	x += 2;
	//	if (i > 0 && i % 200 == 0) {
	//		z += 2;
	//		x = -100;
	//	}
	//}


	Entity skybox = World::scene.CreateEntity("Skybox");
	skybox.AddComponent<SkyboxComponent>(AssetLib::SkyboxLib.skyboxes["Islands"]);
	skybox.AddComponent<MeshComponent>();

	float x = 0;
	float z = 0;
	for (int i = 0; i < 1000; i++) {
		Entity ent = World::scene.CreateEntity("Hello L-System");
		ent.AddComponent<MeshComponent>(CubeMesh::Vertices, CubeMesh::Indices, GL_TRIANGLES);
		ent.AddComponent<MaterialColorComponent>(glm::vec4(1, 1, 1, 1));
		auto component = ent.AddComponent<LSystemComponent>();
		component.SetPreset(Preset1::preset.angle, Preset1::preset.axiom, Preset1::preset.rules);
		component.iteration = 11;
		World::scene.lSystem.Update(ent, component);

		auto& transform = ent.GetComponent<TransformComponent>();
		transform.Position = glm::vec3(x, 0, z);
		transform.dirty = true;

		x += 20;
		if (i > 0 && i % 20 == 0) {
			z += 20;
			x = 0;
		}
	}

	//auto rng = std::default_random_engine{};
	//std::shuffle(std::begin(EntityReg::registry.GetEntities()), std::end(EntityReg::registry.GetEntities()), rng);
	//std::shuffle(std::begin(EntityReg::registry.GetComponents<TransformComponent>()), std::end(EntityReg::registry.GetComponents<TransformComponent>()), rng);
	//std::shuffle(std::begin(EntityReg::registry.GetComponents<MeshComponent>()), std::end(EntityReg::registry.GetComponents<MeshComponent>()), rng);
	//std::shuffle(std::begin(World::scene.GetMaterials()), std::end(World::scene.GetMaterials()), rng);
}

void PlaygroundLevel::Tick(const float delta)
{
}

void PlaygroundLevel::DrawGUI()
{
	Level::DrawGUI();
}

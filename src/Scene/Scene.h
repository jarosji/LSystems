#pragma once

#include "Camera.h"
#include "ECS/Systems/LSystem.h"
#include "ECS/Entity.h"

#include <vector>
#include <iostream>
#include <memory>
#include <map>

class RenderSystem;

struct Scene {

	Scene()
	{
		std::cout << "Scene constructed" << std::endl;
	}

	void Clear() {
		selectedEntity = null_entity;
		entities.clear();
	}

	Entity CreateEntity(const std::string& name, const glm::vec3& position = glm::vec3(0, 0, 1));
	bool DeleteEntity(Entity entity);
	std::map<uint32_t, Entity>& GetEntities();
	Entity& GetEntityRef(uint32_t entityId);
	Entity GetEntity(uint32_t entityId);
	bool ContainsEntity(uint32_t entityId);
public:

	std::map<uint32_t, Entity> entities;
	Entity selectedEntity{ null_entity };

	LSystem lSystem;
	std::vector<std::shared_ptr<RenderSystem>> systems;

	Camera camera;
};

namespace World {
	inline Scene scene;
}
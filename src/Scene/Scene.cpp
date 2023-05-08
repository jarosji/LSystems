#include "Scene.h"

Entity Scene::CreateEntity(const std::string& name, const glm::vec3& position)
{
	Entity entity(EntityReg::registry.Create());
	entity.AddComponent<TransformComponent>(position, glm::vec3(0), glm::vec3(1));
	entity.AddComponent<EntityDescriptorComponent>(entity.GetId(), name);

	entities.emplace(entity.GetId(), entity);

	return entity;
}

bool Scene::DeleteEntity(Entity entity)
{
	entities.erase(entity.GetId());
	entity.Remove();
	return true;
}

std::map<uint32_t, Entity>& Scene::GetEntities()
{
	return entities;
}

Entity& Scene::GetEntityRef(uint32_t entityId)
{
	return entities[entityId];
}

Entity Scene::GetEntity(uint32_t entityId)
{
	return entities[entityId];
}

bool Scene::ContainsEntity(uint32_t entityId)
{
	return entities.count(entityId);
}

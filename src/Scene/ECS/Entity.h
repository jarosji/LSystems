#pragma once
#include <cstdint>
#include "EntityRegistry.h"


class Entity

{
public:

	Entity()
		: entityId(null_entity)
	{
	}
	Entity(const unsigned int id)
		: entityId(id)
	{
	}

	template<typename T, typename ...Args>
	T& AddComponent(Args&&... args) {
		return EntityReg::registry.AddComponent<T>(entityId, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent() {
		return EntityReg::registry.GetComponent<T>(entityId);
	}

	template<typename T>
	bool HasComponent() {
		return EntityReg::registry.HasComponent<T>(entityId);
	}

	bool Remove() {
		return EntityReg::registry.Remove(entityId);
	}


	const uint32_t GetId() const { return entityId; }

	//Light check
	//operator bool() const { return entityId != null_entity; }
	//Deep check
	const bool IsValid() const { return entityId < null_entity; }

	friend bool operator==(const Entity l, const Entity r) { return l.GetId() == r.GetId(); }

private:
	uint32_t entityId;
};
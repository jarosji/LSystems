#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <tuple>

#include "../ECS/Components.h"
#include "../../Math/SparseSet.h"

template<typename ...Types>
class ComponentPool {

	std::tuple<SparseSet<Types>...> vectors;

public:

	template<typename T, typename ...Args>
	T& AddComponent(int entityId, Args... args) {
		return std::get<SparseSet<T>>(vectors).Add(entityId, T(args...));
	}

	template<typename T>
	std::vector<T>& GetComponents() {
		return std::get<SparseSet<T>>(vectors).GetComponents();
	}

	template<typename T>
	SparseSet<T>& GetPools() {
		return std::get<SparseSet<T>>(vectors);
	}

	template<typename T>
	std::vector<int>& GetDense() {
		return std::get<SparseSet<T>>(vectors).GetDense();
	}

	template<typename T>
	T& GetComponent(int entityId) {
		return std::get<SparseSet<T>>(vectors).Find(entityId);
	}

	template<typename T>
	bool HasComponent(int entityId) {
		return std::get<SparseSet<T>>(vectors).Contains(entityId);
	}

	bool Remove(int entityId) {
		Remove_internal(vectors, entityId);
		return true;
	}

	void Clear() {
		Clear_internal(vectors);
	}

private:
	template <size_t I = 0>
	void Remove_internal(std::tuple<SparseSet<Types>...>& componentPools, int entityId) {
		if constexpr (I == sizeof...(Types))
			return;

		else {
			std::get<I>(componentPools).DeleteElement(entityId);
			Remove_internal<I + 1>(componentPools, entityId);
		}
	}

	template <size_t I = 0>
	void Clear_internal(std::tuple<SparseSet<Types>...>& componentPools) {
		if constexpr (I == sizeof...(Types))
			return;

		else {
			std::get<I>(componentPools).Clear();
			Clear_internal<I + 1>(componentPools);
		}
	}
};

class EntityRegistry {

public:

	EntityRegistry()
	{
		std::cout << "entity registry constructed" << std::endl;
	}

	void Clear() {
		pool.Clear();
		lastId = 0;
		//entities.clear();
	}

#pragma region EntityLifetime

	uint32_t Create() {
		return lastId++;
	}
	bool Remove(const uint32_t entity) {
		return pool.Remove(entity);
	}

	template<typename T, typename ... Args>
	T& AddComponent(int entityId, Args&&... args) {
		return pool.AddComponent<T>(entityId, std::forward<Args>(args)...);
	}

#pragma endregion

#pragma region ComponentLifetime
	template<typename T>
	inline std::vector<T>& GetComponents() {
		return pool.GetComponents<T>();
	}

	template<typename T>
	inline T& GetComponent(int entityId) {
		return pool.GetComponent<T>(entityId);
	}

	template<typename T>
	inline bool HasComponent(int entityId) {
		return pool.HasComponent<T>(entityId);
	}

	template<typename T>
	inline std::vector<int>& GetDense() {
		return pool.GetDense<T>();
	}
#pragma endregion

private:

	ComponentPool<TransformComponent, EntityDescriptorComponent, MeshComponent,
		MaterialTextureComponent, MaterialColorComponent,
		DirectionalLight, SpotLight, PointLight,
		SkyboxComponent,
		LSystemComponent> pool;

	uint32_t lastId = 0;
};

namespace EntityReg {
	inline EntityRegistry registry;
}

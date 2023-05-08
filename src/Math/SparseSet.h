#pragma once

#include <vector>

constexpr uint32_t null_entity = 50000; //std::numeric_limits<uint32_t>::max();

template <typename T>
class SparseSet {
public:

    SparseSet()
    {
        sparse = std::vector<int>(null_entity, null_entity); //TODO: make more dynamic
    }

    ~SparseSet()
    {
    }

    T& Find(int entityId) {
        return components[sparse[entityId]];
    }

    bool Contains (int entityId) {
        return entityId < sparse.size() && sparse[entityId] < dense.size() && dense[sparse[entityId]] == entityId;
    }

    T& Add(int entityId, T component) {
        dense.push_back(entityId);

        sparse[entityId] = dense.size() - 1;

        //dense.size() - 1;

        return components.emplace_back(std::move(component));
    }

    void DeleteElement(int x) {
        //int pos = find(sparse.begin(), sparse.end(), dense.size() - 1) - sparse.begin();

        if (!Contains(x))
            return;

        //components[sparse[x]] = std::move(components.back());

        //const auto last = dense.back();
        //dense[sparse[x]] = dense.back();
        //
        //sparse[x] = sparse[last];

        const auto last = dense.back();
        std::swap(components.back(), components[sparse[x]]);
        std::swap(dense.back(), dense[sparse[x]]);
        std::swap(sparse[last], sparse[x]);

        //sparse[x] = -1;
        components.pop_back();
        dense.pop_back();
    }

    std::vector<int>& GetDense() {
        return dense;
    }

    std::vector<T>& GetComponents() {
        return components;
    }

    void Clear() {
        components.clear();
        dense.clear();
        sparse = std::vector<int>(null_entity, null_entity);
    }

private:
    std::vector<T> components;
    std::vector<int> dense;
    std::vector<int> sparse;
};


#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "System.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stack>
#include <queue>
#include "../Entity.h"

#include <future>
#include "../../../Math/Vertex.h"

struct LSystemComponent;

struct Save {
	glm::vec3 point;
	glm::quat	 dir;
	int index;
};

struct Preset {
	std::vector<Rule> rules;
	std::string axiom;
	float angle;
};

struct Preset1 {
	static const Preset preset;
};
struct Preset2 {
	static const Preset preset;
};
struct Preset3 {
	static const Preset preset;
};
struct Preset4 {
	static const Preset preset;
};

class LSystem : public System{
public:

	struct ThreadData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Entity ent;
	};

	virtual void Tick(const float delta) override;
	void Update(Entity entity, LSystemComponent component);
	void Clear();

private:
	std::vector<std::future<void>> futures;
	
	std::queue<ThreadData> data;

	static void Generate(std::queue<ThreadData>& dat, Entity entity, LSystemComponent component);

	static void Turte(const LSystemComponent component,
	std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

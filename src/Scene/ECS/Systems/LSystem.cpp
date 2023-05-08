#include "LSystem.h"

#include "../../../Application/Application.h"
#include <thread>
#include "../Components.h"

const Preset Preset1::preset = {
	{
		Rule{"A", "[B]////[B]////[B]"},
		Rule{"B", "&FFFA"},
	},
	"FFFA", 28

};

const Preset  Preset2::preset = {
	{
		Rule{"F", "F[+FF][-FF]F[-F][+F]F"}
	},
	"F", 35
};

const Preset Preset3::preset = {
	{
		Rule{"X", "X[-FFF][+FFF]FX"},
		Rule{"Y", "YFX[+Y][-Y]"},
	},
	"Y", 25.7f
};

const Preset Preset4::preset = {
	{
		Rule{"F", "FF+[+F-F-F]-[-F+F+F]"},
	},
	"F", 22.5f
};


static std::mutex dataMutex;
void LSystem::Tick(const float delta)
{
	if(!data.empty()) {
		ThreadData& dat = data.front();
		if(World::scene.ContainsEntity(dat.ent.GetId()))
		
		dat.ent.GetComponent<MeshComponent>().Generate(dat.vertices, dat.indices, GL_LINES);

		
		data.pop();
	}
}

void LSystem::Update(const Entity entity, LSystemComponent component)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	component.sentence = component.axiom;

#if ASYNC
	futures.push_back(std::async(std::launch::async, &LSystem::Generate, std::ref(data), entity, component));
#else
	Generate(data, entity, component);
#endif
}

void LSystem::Clear()
{
	for (auto& future : futures) {
		future.get();
	}
	futures.clear();
	std::queue<ThreadData> empty;
	std::swap(data, empty);
}


void LSystem::Generate(std::queue<ThreadData>& dat, Entity entity, LSystemComponent component)
{
	for (int i = 0; i < component.iteration; i++) {
		std::string nextSentence = "";
		for (unsigned int i = 0; i < component.sentence.length(); i++) {
			char current = component.sentence[i];
			bool found = false;
			for (unsigned int j = 0; j < component.rules.size(); j++) {
				if (current == component.rules[j].a[0]) {
					nextSentence += component.rules[j].b;
					found = true;
					break;
				}
			}
			if (!found) {
				nextSentence += current;
			}
		}
		component.sentence = nextSentence;

#ifdef _DEBUG
		std::cout << component.sentence << std::endl;
#endif
	}

	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;
	Turte(component, verts, inds);

	ThreadData d({verts, inds, entity});

	std::lock_guard<std::mutex> lock(dataMutex);
	dat.push(d);
}

void LSystem::Turte(const LSystemComponent component,
	std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	std::stack<Save> saves;

	glm::vec3 point = glm::vec3(0);

	glm::quat dir = glm::angleAxis(glm::radians(component.angle), glm::vec3(0, 1, 0));

	unsigned int index = 0;
	int saveIndex = -1;
	bool popIndex = false;

	int oldIndex = 0;

	vertices.emplace_back(Vertex{ point, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {0.0f, 0.0f } });

	for (unsigned int i = 0; i < component.sentence.length(); i++) {
		char current = component.sentence[i];

		switch (current) {
		case 'F': {
			index++;
			oldIndex = index;

			if (!popIndex) {
				indices.emplace_back(index - 1);
			}
			else { indices.emplace_back(saveIndex); }
			popIndex = false;
			indices.emplace_back(index);

			point += dir * glm::vec3(0, 1, 0);
			vertices.emplace_back(Vertex{ point, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {0.0f, 0.0f } });
			break;
		}
		case '+': {
			dir *= glm::angleAxis(glm::radians(component.angle), glm::vec3(0, 0, 1));
			break;
		}
		case '-': {
			dir *= glm::angleAxis(glm::radians(-component.angle), glm::vec3(0, 0, 1));
			break;
		}
		case '/': {
			dir *= glm::angleAxis(glm::radians(component.angle), glm::vec3(0, 1, 0));
			break;
		}
		case '\\': {
			dir *= glm::angleAxis(glm::radians(-component.angle), glm::vec3(0, 1, 0));
			break;
		}
		case '&': {
			dir *= glm::angleAxis(glm::radians(component.angle), glm::vec3(1, 0, 0));
			break;
		}
		case '^': {
			dir *= glm::angleAxis(glm::radians(-component.angle), glm::vec3(1, 0, 0));
			break;
		}
		case '[': {
			Save save;
			save.dir = dir;
			save.point = point;
			save.index = oldIndex;
			saves.push(save);

			break;
		}
		case ']': {
			Save save = saves.top();
			saves.pop();

			dir = save.dir;
			point = save.point;

			popIndex = true;
			saveIndex = save.index;

			oldIndex = save.index;

			break;
		}
		}
	}
}

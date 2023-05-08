#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext/vector_float3.hpp>

#include "../../Renderer/Buffer/VertexArray.h"
#include "../../Renderer/Buffer/IndexBuffer.h"
#include "../../Renderer/Buffer/VertexBufferLayout.h"
#include "../../Renderer/Buffer/VertexBuffer.h"
#include "../../Renderer/Texture/Texture.h"
#include "../../Renderer/Shader/Shader.h"
#include "../../Renderer/Texture/Skybox.h"
#include "Systems/RenderSystem.h"

#include "../AssetLib.h"

struct TransformComponent {
	TransformComponent()
		: Position(glm::vec3(0)), Rotation(glm::vec3(0)), Scale(glm::vec3(1)), ModelMat(glm::mat4(1))
	{
		GetModelMat();
	}
	TransformComponent(const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 scale)
		: Position(pos), Rotation(rot), Scale(scale), ModelMat(glm::mat4(1))
	{
		GetModelMat();
	}

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 ModelMat;

	glm::mat4 GetModelMat() {

		if (!dirty) {
			return ModelMat;
		}

		ModelMat = glm::translate(glm::mat4(1.0f), Position);

		ModelMat = glm::rotate(ModelMat, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMat = glm::rotate(ModelMat, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMat = glm::rotate(ModelMat, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMat = glm::scale(ModelMat, Scale);

		dirty = false;

		return ModelMat;
	}

	bool dirty = true;
};

struct MeshComponent {
	MeshComponent()
		: Vertices(CubeMesh::Vertices), Indices(CubeMesh::Indices), Ibo(CubeMesh::Indices, CubeMesh::Indices.size())
	{
		VertexBuffer vb(CubeMesh::Vertices, CubeMesh::Vertices.size() * 8 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		Vao.AddBuffer(vb, layout);

		vb.Unbind();
		Vao.Unbind();
		Ibo.Unbind();
	}

	MeshComponent(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, int type)
		: Vertices(vertices), Indices(indices), Ibo(indices, indices.size())
	{
		VertexBuffer vb(vertices, vertices.size() * 8 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		Vao.AddBuffer(vb, layout);

		vb.Unbind();
		Vao.Unbind();
		Ibo.Unbind();
	}

	void Generate(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, int type)
	{
		VertexBuffer vb(vertices, vertices.size() * 8 * sizeof(float));

		Ibo = IndexBuffer(indices, indices.size());

		Vao = VertexArray();
		Vao.SetType(type);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		Vao.AddBuffer(vb, layout);

		vb.Unbind();
		Vao.Unbind();
		Ibo.Unbind();
	}

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	//TODO: Hacky? Batching?
	VertexArray Vao;
	IndexBuffer Ibo;
};

struct MaterialColorComponent {

	MaterialColorComponent()
		: Color(glm::vec4(1, 1, 1, 1))
	{
	}

	MaterialColorComponent(const glm::vec4 color)
		:Color(color)
	{
	}
	
	glm::vec4 Color;

	//Texture DiffuseTex;
	//Texture SpecularTex;
	//float Shinnines;
};

struct MaterialTextureComponent {

	MaterialTextureComponent()
		: DiffuseTex(nullptr), SpecularTex(nullptr), Shinnines(32)
	{
	}

	MaterialTextureComponent(Texture* diffuseTex, Texture* specularTex, float shinnines)
		: DiffuseTex(diffuseTex), SpecularTex(specularTex), Shinnines(shinnines)
	{
	}

	glm::vec4 Color = glm::vec4(1, 1, 1, 1);
	Texture* DiffuseTex;
	Texture* SpecularTex;
	float Shinnines;
};

struct EntityDescriptorComponent {

	EntityDescriptorComponent()
		: Id(-1), Name("")
	{
	}
	EntityDescriptorComponent(const int id, const std::string& name)
		: Id(id), Name(name)
	{
	}

	int Id;
	std::string Name;
};

struct SkyboxComponent {

	//SkyboxComponent() : Skybox(std::string()[6])
	//{
	//}
	SkyboxComponent(Skybox skybox)
		: Skybox(skybox)
	{
	}

	Skybox Skybox;
};

struct Rule {
	std::string a;
	std::string b;
};

struct LSystemComponent {

	LSystemComponent()
	{
	}

	void SetPreset(const int inAngle, const std::string& inAxiom, const std::vector<Rule>& inRules)
	{
		angle = inAngle;
		axiom = inAxiom;
		rules = inRules;
	}

	float length = 1;
	float angle = 25.0f;

	int iteration = 1;

	std::string axiom;
	std::string sentence;

	std::vector<Rule> rules;
};

#pragma region Lights

struct DirectionalLight {

	DirectionalLight()
	{
		Ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		Specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

};

struct PointLight
{
public:
	PointLight()
	{
		Ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		Specular = glm::vec3(1.0f, 1.0f, 1.0f);

		Constant = 1;
		Linear = 0.09f;
		Quadratic = 0.032f;
	}

	int Index = 0;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;

};

struct SpotLight
{

public:

	SpotLight()
	{
		Ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		Specular = glm::vec3(1.0f, 1.0f, 1.0f);

		Constant = 1;
		Linear = 0.09f;
		Quadratic = 0.032f;
		CutOff = 12.5f;
		OuterCutOff = 15.0f;
	}

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;
	float CutOff;
	float OuterCutOff;
};

#pragma endregion
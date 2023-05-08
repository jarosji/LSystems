#include "RenderSystem.h"
#include "../../../Renderer/Renderer.h"
#include "../../../Scene/Scene.h"
#include "../../AssetLib.h"
#include "../Components.h"
#include "../EntityRegistry.h"

const std::vector<Vertex> CubeMesh::Vertices = {
		Vertex { glm::vec3{-0.5f, -0.5f, 0.5f }, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {0.0f, 0.0f }}, //0
		Vertex { glm::vec3{ 0.5f, -0.5f, 0.5f }, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {1.0f, 0.0f }}, //1
		Vertex { glm::vec3{ 0.5f,  0.5f, 0.5f }, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {1.0f, 1.0f }}, //2
		Vertex { glm::vec3{-0.5f,  0.5f, 0.5f }, glm::vec3{ 0.0f,  0.0f, 1.0f }, glm::vec2 {0.0f, 1.0f }}, //3

		Vertex { glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec3{ 1.0f,  0.0f, 0.0f }, glm::vec2 {0.0f, 0.0f }}, //4
		Vertex { glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 1.0f,  0.0f, 0.0f }, glm::vec2 {1.0f, 0.0f }}, //5
		Vertex { glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 1.0f,  0.0f, 0.0f }, glm::vec2 {1.0f, 1.0f }}, //6
		Vertex { glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec3{ 1.0f,  0.0f, 0.0f }, glm::vec2 {0.0f, 1.0f }}, //7

		Vertex { glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f,  0.0f, -1.0f }, glm::vec2 {1.0f, 1.0f }}, //8
		Vertex { glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f,  0.0f, -1.0f }, glm::vec2 {0.0f, 1.0f }}, //9
		Vertex { glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f,  0.0f, -1.0f }, glm::vec2 {0.0f, 0.0f }}, //10
		Vertex { glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f,  0.0f, -1.0f }, glm::vec2 {1.0f, 0.0f }}, //11

		Vertex { glm::vec3{-0.5f, -0.5f,  0.5f }, glm::vec3{ -1.0f,  0.0f, 0.0f }, glm::vec2 {1.0f, 1.0f }}, //12
		Vertex { glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{ -1.0f,  0.0f, 0.0f }, glm::vec2 {0.0f, 1.0f }}, //13
		Vertex { glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{ -1.0f,  0.0f, 0.0f }, glm::vec2 {0.0f, 0.0f }}, //14
		Vertex { glm::vec3{-0.5f,  0.5f,  0.5f }, glm::vec3{ -1.0f,  0.0f, 0.0f }, glm::vec2 {1.0f, 0.0f }}, //15

		Vertex { glm::vec3{-0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2 {1.0f, 1.0f }}, //16
		Vertex { glm::vec3{ 0.5f, -0.5f,  0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2 {0.0f, 1.0f }}, //17
		Vertex { glm::vec3{ 0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2 {0.0f, 0.0f }}, //18
		Vertex { glm::vec3{-0.5f, -0.5f, -0.5f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec2 {1.0f, 0.0f }}, //19

		Vertex { glm::vec3{-0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2 {1.0f, 1.0f }}, //16
		Vertex { glm::vec3{ 0.5f,  0.5f,  0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2 {0.0f, 1.0f }}, //17
		Vertex { glm::vec3{ 0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2 {0.0f, 0.0f }}, //18
		Vertex { glm::vec3{-0.5f,  0.5f, -0.5f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec2 {1.0f, 0.0f }}, //19
};
const std::vector<unsigned int> CubeMesh::Indices = {
			 0, 1, 2,
			 2, 3, 0,

			 4, 5, 6,
			 6, 7, 4,

			 8, 9, 10,
			 10, 11, 8,

			 12, 13, 14,
			 14, 15, 12,

			 16, 17, 18,
			 18, 19, 16,

			 20, 21, 22,
			 22, 23, 20,
};

RenderSystem::RenderSystem()
{
}


//This here is a giant mess - mainly because of missing functionalities of SparseSet (sorting, grouping, views, iterators),
//but at least it works (also performance-- while using indirection)

void RenderSystem::Tick(const float deltaTime)
{
	const glm::mat4& vp = World::scene.camera.GetProjMat() * World::scene.camera.GetViewMat();

	std::vector<TransformComponent>& transforms = EntityReg::registry.GetComponents<TransformComponent>();
	std::vector<MeshComponent>& meshes = EntityReg::registry.GetComponents<MeshComponent>();
	std::vector<int>& meshesDense = EntityReg::registry.GetDense<MeshComponent>();

	std::vector<int>& directionalLights = EntityReg::registry.GetDense<DirectionalLight>();
	std::vector<int>& spotLights = EntityReg::registry.GetDense<SpotLight>();
	std::vector<int>& pointLights = EntityReg::registry.GetDense<PointLight>();

	std::vector<int>& skyboxDense = EntityReg::registry.GetDense<SkyboxComponent>();

	std::vector<MaterialColorComponent>& materialColors = EntityReg::registry.GetComponents<MaterialColorComponent>();
	std::vector<int>& materialColorsDense = EntityReg::registry.GetDense<MaterialColorComponent>();

	std::vector<MaterialTextureComponent>& materialTextures = EntityReg::registry.GetComponents<MaterialTextureComponent>();
	std::vector<int>& materialTexturesDense = EntityReg::registry.GetDense<MaterialTextureComponent>();

	AssetLib::ShaderLib.shaders["Basic"].Bind();
	for (unsigned int i = 0; i < materialColors.size(); i++) {
		const int entityId = materialColorsDense[i];
		MaterialColorComponent& material = materialColors[i];
		MeshComponent& mesh = EntityReg::registry.GetComponent<MeshComponent>(entityId);
		TransformComponent& transform = EntityReg::registry.GetComponent<TransformComponent>(entityId);

		const glm::mat4& mvp = vp * transform.GetModelMat();
		AssetLib::ShaderLib.shaders["Basic"].SetUniformMat4f("u_MVP", mvp);
		AssetLib::ShaderLib.shaders["Basic"].SetUniform4f("u_Color", material.Color);

		Renderer::Draw(mesh.Vao, mesh.Ibo);
	}

	Shader& lightShader = AssetLib::ShaderLib.shaders["Light"];
	lightShader.Bind();
	for (unsigned int i = 0; i < directionalLights.size(); i++) {
		const int entityId = directionalLights[i];
		DirectionalLight& light = EntityReg::registry.GetComponent<DirectionalLight>(entityId);
		TransformComponent& transform = EntityReg::registry.GetComponent<TransformComponent>(entityId);

		lightShader.SetUniform3f("u_DirLight.direction", transform.Rotation / -360.0f);
		lightShader.SetUniform3f("u_DirLight.ambient", light.Ambient);
		lightShader.SetUniform3f("u_DirLight.diffuse", light.Diffuse);
		lightShader.SetUniform3f("u_DirLight.specular", light.Specular);
	}

	for (unsigned int i = 0; i < spotLights.size(); i++) {
		const int entityId = spotLights[i];
		SpotLight& light = EntityReg::registry.GetComponent<SpotLight>(entityId);
		TransformComponent& transform = EntityReg::registry.GetComponent<TransformComponent>(entityId);

		lightShader.SetUniform3f("u_SpotLight.position", transform.Position);
		lightShader.SetUniform3f("u_SpotLight.direction", transform.Rotation / -360.0f);
		lightShader.SetUniform3f("u_SpotLight.ambient", light.Ambient);
		lightShader.SetUniform3f("u_SpotLight.diffuse", light.Diffuse);
		lightShader.SetUniform3f("u_SpotLight.specular", light.Specular);
		lightShader.SetUniform1f("u_SpotLight.constant", light.Constant);
		lightShader.SetUniform1f("u_SpotLight.linear", light.Linear);
		lightShader.SetUniform1f("u_SpotLight.quadratic", light.Quadratic);
		lightShader.SetUniform1f("u_SpotLight.cutOff", glm::cos(glm::radians(light.CutOff)));
		lightShader.SetUniform1f("u_SpotLight.outerCutOff", glm::cos(glm::radians(light.OuterCutOff)));
	}

	for (unsigned int i = 0; i < pointLights.size(); i++) {
		const int entityId = pointLights[i];
		PointLight& light = EntityReg::registry.GetComponent<PointLight>(entityId);
		TransformComponent& transform = EntityReg::registry.GetComponent<TransformComponent>(entityId);

		lightShader.SetUniform3f("u_PointLights[" + std::to_string(i) + "].position", transform.Position);
		lightShader.SetUniform3f("u_PointLights[" + std::to_string(i) + "].ambient", light.Ambient);
		lightShader.SetUniform3f("u_PointLights[" + std::to_string(i) + "].diffuse", light.Diffuse);
		lightShader.SetUniform3f("u_PointLights[" + std::to_string(i) + "].specular", light.Specular);
		lightShader.SetUniform1f("u_PointLights[" + std::to_string(i) + "].constant", light.Constant);
		lightShader.SetUniform1f("u_PointLights[" + std::to_string(i) + "].linear", light.Linear);
		lightShader.SetUniform1f("u_PointLights[" + std::to_string(i) + "].quadratic", light.Quadratic);
	}

	for (unsigned int i = 0; i < materialTextures.size(); i++) { //skyboxDense.size()
		const int entityId = materialTexturesDense[i];
		MaterialTextureComponent& material = materialTextures[i];
		MeshComponent& mesh = EntityReg::registry.GetComponent<MeshComponent>(entityId);
		TransformComponent& transform = EntityReg::registry.GetComponent<TransformComponent>(entityId);

		material.DiffuseTex->Bind();
		material.SpecularTex->Bind(1);
		lightShader.SetUniform1i("u_Material.diffuse", 0);
		lightShader.SetUniform1i("u_Material.specular", 1);
		lightShader.SetUniform1f("u_Material.shininess", material.Shinnines);

		
		const glm::mat4& mvp = vp * transform.GetModelMat();
		lightShader.SetUniformMat4f("u_MVP", mvp);
		lightShader.SetUniformMat4f("u_Model", transform.GetModelMat()); //BAD
		lightShader.SetUniform3f("u_View", World::scene.camera.GetPosition()); //BAD
		lightShader.SetUniform4f("u_Material.diffuseColor", material.Color); //BAD

		Renderer::Draw(mesh.Vao, mesh.Ibo);
	}

	Shader& skyboxShader = AssetLib::ShaderLib.shaders["Skybox"];
	skyboxShader.Bind();
	for (int i = 0; i < skyboxDense.size(); i++) {
		const int entityId = skyboxDense[i];
		SkyboxComponent& skybox = EntityReg::registry.GetComponent<SkyboxComponent>(entityId);
		MeshComponent& mesh = EntityReg::registry.GetComponent<MeshComponent>(entityId);

		glDepthFunc(GL_LEQUAL);

		glm::mat4 v = glm::mat4(glm::mat3(World::scene.camera.GetViewMat()));
		glm::mat4 p = World::scene.camera.GetProjMat();
		skyboxShader.SetUniformMat4f("view", v);
		skyboxShader.SetUniformMat4f("projection", p);

		skybox.Skybox.Bind();
		Renderer::Draw(mesh.Vao, mesh.Ibo);

		glDepthFunc(GL_LESS);
	}
}

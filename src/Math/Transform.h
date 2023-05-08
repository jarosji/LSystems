#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform()
		: position(glm::vec3(0)), rotation(glm::vec3(0)), scale(glm::vec3(1)), modelMat(glm::mat4(1))
	{
		CalculateModelMatrix();
	}

	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: position(glm::vec3(position)), rotation(glm::vec3(rotation)), scale(glm::vec3(scale)), modelMat(glm::mat4(1))
	{
		CalculateModelMatrix();
	}

	void SetPosition(const glm::vec3& NewLocation) {
		position = NewLocation;
		CalculateModelMatrix();
	}
	void Translate(const glm::vec3& NewLocation) {
		position += NewLocation;
		CalculateModelMatrix();
	}
	void SetRotation(const glm::vec3& NewRotation)
	{
		rotation = NewRotation;
		CalculateModelMatrix();
	}
	void Rotate(const glm::vec3& NewRotation)
	{
		rotation += NewRotation;
		CalculateModelMatrix();
	}
	void SetScale(const glm::vec3& NewScale)
	{
		scale = NewScale;
		CalculateModelMatrix();
	}
	void Scale(const glm::vec3& NewScale)
	{
		scale += NewScale;
		CalculateModelMatrix();
	}

	const glm::vec3& GetPosition() const { return position; }
	const glm::vec3& GetRotation() const { return rotation; }
	const glm::vec3& GetScale() const { return scale; }
	const glm::mat4& GetModelMat() const { return modelMat; }

	void CalculateModelMatrix() {
		modelMat = glm::translate(glm::mat4(1.0f), position);
		modelMat = glm::rotate(modelMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMat = glm::rotate(modelMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMat = glm::rotate(modelMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::scale(modelMat, scale);
	}

private:
	

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	//glm::mat4 translationMat;
	//glm::mat4 orientationMat;
	//glm::mat4 scalingMat;

	glm::mat4 modelMat;
};


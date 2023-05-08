#pragma once

#include "../Math/Transform.h"

class Window;

enum class ViewType {
	NONE = -1, ORTHO = 0, PERSPECTIVE = 1
};

class Camera {
public:

	Camera();
	Camera(const float width, const float height);

	const glm::mat4& GetViewMat() const;
	const glm::mat4& GetProjMat() const;
	void SetProjMat(ViewType viewType, float width, float height);

	const glm::vec3& GetPosition() const;
	const glm::vec3& GetRotation() const;
	const glm::vec3& GetUp() const;

	//Should be on Actor?
	void Tick(const float delta);

	//TRANSFORMS
	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);

	void MoveForward(const float axis);
	void MoveLeft(const float axis);
	void MoveUp(const float axis);
	void Rotate(float rotX, float rotY);
	//~TRANSFORMS

	void AdjustSpeed(const double axis);

private:
	Window* window;

	Transform transform;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 0.15f;
	float speedStep = 0.005f;

	glm::mat4 proj;
	glm::mat4 view;

	//Controls
	double smouseX = 0;
	double smouseY = 0;
	bool firstClick = true;
	float sensitivity = 0.1f;
};
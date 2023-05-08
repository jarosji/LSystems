#include "Camera.h"

#include <ImGUI/imgui.h>
#include <iostream>

#include "../Application/Application.h"
#include "../Application/Window.h"
#include <GLFW/glfw3.h>
#include "../Math/Math.h"

Camera::Camera()
	: proj(glm::mat4(1)), view(glm::mat4(1))
{
	transform.SetRotation(glm::vec3(0, 0, 1));
}

Camera::Camera(const float width, const float height)
	: proj(glm::mat4(1)), view(glm::mat4(1))
{
	SetProjMat(ViewType::PERSPECTIVE, width, height);
}

const glm::mat4& Camera::GetViewMat() const
{
	return view;
}

const glm::mat4& Camera::GetProjMat() const
{
	return proj;
}

void Camera::SetProjMat(ViewType viewType, float width, float height)
{
	switch (viewType) {
	case ViewType::ORTHO: {
		proj = glm::ortho(0.0f, width, 0.0f, height, 0.1f, 100.0f);
		break;
	}
	case ViewType::PERSPECTIVE: {
		proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 2000.0f);
		break;
	}
	}
}

const glm::vec3& Camera::GetPosition() const
{
	return transform.GetPosition();
}

const glm::vec3& Camera::GetRotation() const
{
	return transform.GetRotation();
}

const glm::vec3& Camera::GetUp() const
{
	return up;
}

void Camera::Tick(const float delta)
{
	window = &Application::GetApplication()->GetWindow();

	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_W))
	{
		MoveForward(speed  * delta);
	}
	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_A))
	{
		MoveLeft(-speed * delta);
	}
	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_S))
	{
		MoveForward(-speed * delta);
	}
	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_D))
	{
		MoveLeft(speed * delta);
	}

	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_E))
	{
		MoveUp(speed * delta);
	}
	if (glfwGetKey(window->GetGlfwWindow(), GLFW_KEY_Q))
	{
		MoveUp(-speed * delta);
	}

	//MOUSE
	if (glfwGetMouseButton(window->GetGlfwWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		if (firstClick) {
			glfwGetCursorPos(window->GetGlfwWindow(), &smouseX, &smouseY);
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window->GetGlfwWindow(), &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - smouseY);
		float rotY = sensitivity * (float)(mouseX - smouseX);

		Rotate(rotX, rotY);

		glfwSetCursorPos(window->GetGlfwWindow(), smouseX, smouseY);
	}
	else if (glfwGetMouseButton(window->GetGlfwWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		if (firstClick == false) {
			//glfwSetCursorPos(window->GetGlfwWindow(), smouseX, smouseY);
			firstClick = true;
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void Camera::SetPosition(const glm::vec3& position)
{
	transform.SetPosition(position);

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::SetRotation(const glm::vec3& rotation)
{
	transform.SetRotation(glm::rotate(transform.GetRotation(), glm::radians(rotation.x), up));
	transform.SetRotation(glm::rotate(transform.GetRotation(), glm::radians(rotation.y), up));
	transform.SetRotation(glm::rotate(transform.GetRotation(), glm::radians(rotation.z), up));

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::MoveForward(const float axis)
{
	//view = glm::translate(view, glm::vec3(0, 0, axis)); 
	const glm::vec3& pos = transform.GetPosition() + axis * speed * transform.GetRotation();
	transform.SetPosition(pos);

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::MoveLeft(const float axis)
{
	//view = glm::translate(view, glm::vec3(axis, 0, 0)); 
	const glm::vec3& pos = transform.GetPosition() + axis * speed * glm::normalize(glm::cross(transform.GetRotation(), up));
	transform.SetPosition(pos);

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::MoveUp(const float axis)
{
	const glm::vec3& pos = transform.GetPosition() + axis * speed * up;
	transform.SetPosition(pos);

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::Rotate(float rotX, float rotY)
{
	transform.SetRotation(glm::rotate(transform.GetRotation(), glm::radians(-rotX), glm::normalize(glm::cross(transform.GetRotation(), up))));
	transform.SetRotation(glm::rotate(transform.GetRotation(), glm::radians(-rotY), up));

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetRotation(), up);
}

void Camera::AdjustSpeed(const double axis)
{
	double newSpeed = speed + axis * speedStep; 
	speed = Math::Clamp(newSpeed, 0.1f, 2);
	//speed += axis * speedStep;
}

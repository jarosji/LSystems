#pragma once

#include <functional>

struct GLFWwindow;
class Event;

class Window
{
public:
	Window(const int width, const int height);
	~Window();

	void StartFrame();
	void EndFrame();

	using EventCallbackFn = std::function<void(Event&)>;
	void RegisterEvent(const EventCallbackFn& callback);

	void EnableVSync(const bool isEnabled);

	const bool GetWindowShouldClose() const;
	GLFWwindow* GetGlfwWindow() const { return glfwWindow; }

	const int GetWidth() const { return data.width; }
	const int GetHeight() const { return data.height; }

private:
	GLFWwindow* glfwWindow;

	struct WindowData
	{
		unsigned int width, height;

		EventCallbackFn eventCallback;
	};
	WindowData data;
};


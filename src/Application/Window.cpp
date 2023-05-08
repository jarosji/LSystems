#include "Window.h"
#include "../Events/Event.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

Window::Window(const int width, const int height)
{
	data.width = width;
	data.height = height;

	if (glfwInit() != GLFW_TRUE)
		std::cout << "Failed to init GLFW" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	glfwWindow = glfwCreateWindow(width, height, "LSystems", nullptr, nullptr);
	if (glfwWindow == nullptr) {
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(glfwWindow);

	EnableVSync(true);

	glfwSetWindowUserPointer(glfwWindow, &data);
	glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		WindowResizeEvent event(width, height);
		data.eventCallback(event);

	});

	glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

		if (action == GLFW_PRESS) {
			KeyPressedEvent event(key, scancode, mods);
			data.eventCallback(event);
		}
	});

	glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		ScrollEvent event(xoffset, yoffset);
		data.eventCallback(event);
	});
	
		

	//ImGUI
	ImGui::CreateContext();
	ImGuiIO* io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}

void Window::StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(glfwWindow);

	glfwPollEvents();
}

void Window::RegisterEvent(const EventCallbackFn& callback)
{
	data.eventCallback = callback;
}

void Window::EnableVSync(const bool isEnabled)
{
	glfwSwapInterval(isEnabled);
}

const bool Window::GetWindowShouldClose() const
{
	return glfwWindowShouldClose(glfwWindow);
}

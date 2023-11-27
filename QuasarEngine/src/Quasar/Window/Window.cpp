#include "qspch.h"
#include "Window.h"

namespace Quasar
{
	Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name} 
	{
		InitWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);
	}

	void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to create Window Surface");
		}
	}

	void Window::FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto qsWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		qsWindow->framebufferResized = true;
		qsWindow->width = width;
		qsWindow->height = height; 

	}
}
